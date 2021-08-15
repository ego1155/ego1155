#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

#include <poll.h>

#include <libssh/libssh.h>

/**
 * 
 * This program creates a SSH tunnel between clinet  
 * and a server running at REMOTE_HOST on REMOTE_PORT.
 *
 * This program does not includes the client progarm nor 
 * the server program. This example works well with echo server 
 * http://www.paulgriffiths.net/program/c/echoserv.php and 
 * telnet can be used as client program. Also this program 
 * will need change depending on the payload protocol.
 * 
 * Prerequsite  : libssh (libssh.org)
 * Compile      : gcc -o ssh_tunnel ssh_tunnel.c -lpthread -lssh
 *
 * This example is written by Rituparna Kashyap for webyog.com/blog
 */ 

const int   TRUE        = 1;                     
const int   FALSE       = 0;
const char  *LOCALHOST  = "127.0.0.1";      // Localhost
const int   LOCALPORT   = 2222;             // Localport which is used for tunneling  
const char  *SSH_HOST   = "192.168.1.16";   // SSH host 
const char  *SSH_USER   = "root";           // SSH user
const char  *REMOTE_HOST= "192.168.1.99";   // Remote host where the echo server is running
const int   REMOTE_PORT = 12345;             // Port on which the echo server is running

const int BUFFER_SIZE = 1024;               // Size of the buffer while receiving and sending

// structure which is passed as a parameter to the thread
struct tunnel_t {
    int sockdesc;
    ssh_session session;
};

int verify_knownhost(ssh_session);  // Verify is the SSH_HOST is known host or not  
ssh_channel open_ssh_tunnel(ssh_session, const char*, int); // Creates an SSH tunnel between the client and echo server
int close_ssh_tunnel(ssh_channel);  // Close the SSH tunnel

int open_local_port(ssh_session, pthread_t *); // Opens a local port on which the client request the data
void *listen_on_local_port(void *); // Thread function

int main () {

    ssh_session my_ssh_session;
    ssh_channel ssh_tunnel_channel;
    int rc = 0;
    char *password;
    pthread_t thread;

    // Open session and set options
    my_ssh_session = ssh_new();

    if (my_ssh_session == NULL)
        return EXIT_FAILURE;

    ssh_options_set(my_ssh_session, SSH_OPTIONS_HOST, SSH_HOST);
    ssh_options_set(my_ssh_session, SSH_OPTIONS_USER, SSH_USER);

    // Connect to server
    rc = ssh_connect(my_ssh_session);
    if (rc != SSH_OK) {
        fprintf(stderr, "Error connecting to localhost: %s\n",
        ssh_get_error(my_ssh_session));
        ssh_free(my_ssh_session);
        return EXIT_FAILURE;
    } 

    // Verify the server's identity
    // For the source code of verify_knowhost(), check previous example
    if (verify_knownhost(my_ssh_session) < 0) {
        ssh_disconnect(my_ssh_session);
        ssh_free(my_ssh_session);
        return EXIT_FAILURE;
    }

    // Authenticate to the SSH server
    password = getpass("Password: ");
    rc = ssh_userauth_password(my_ssh_session, NULL, "RonaldO9JerseY");
    if (rc != SSH_AUTH_SUCCESS){
        fprintf(stderr, "Error authenticating with password: %s\n",
        ssh_get_error(my_ssh_session));
        ssh_disconnect(my_ssh_session);
        ssh_free(my_ssh_session);
        return EXIT_FAILURE;
    }

    // Open the local port
    if(open_local_port(my_ssh_session, &thread) != -1) {

        // Wait for the thread, created in the open_local_port to exit
        pthread_join(thread, (void *)&rc);
    }
    // disconnect and free the SSH session
    ssh_disconnect(my_ssh_session);
    ssh_free(my_ssh_session);
    return EXIT_SUCCESS; 
}

// Verifies if the SSH server is knowhost, if not make a entry into the knownhost file
int verify_knownhost(ssh_session session) {
    int state, hlen;
    unsigned char *hash = NULL;
    char *hexa;
    char buf[10];

    // Check if the server is known or not
    state = ssh_is_server_known(session);

    hlen = ssh_get_pubkey_hash(session, &hash);
    if (hlen < 0)
        return -1;

    switch (state) {
        case SSH_SERVER_KNOWN_OK:
            break; // ok

        case SSH_SERVER_KNOWN_CHANGED:
            fprintf(stderr, "Host key for server changed: it is now:\n");
            ssh_print_hexa("Public key hash", hash, hlen);
            fprintf(stderr, "For security reasons, connection will be stopped\n");
            free(hash);
            return -1;

        case SSH_SERVER_FOUND_OTHER:
            fprintf(stderr, "The host key for this server was not found but an other"
                "type of key exists.\n");
            fprintf(stderr, "An attacker might change the default server key to"
                "confuse your client into thinking the key does not exist\n");
            free(hash);
            return -1;

        case SSH_SERVER_FILE_NOT_FOUND:
            fprintf(stderr, "Could not find known host file.\n");
            fprintf(stderr, "If you accept the host key here, the file will be"
                "automatically created.\n");
            // fallback to SSH_SERVER_NOT_KNOWN behavior

        case SSH_SERVER_NOT_KNOWN: // Enter the server hex in the know host file if the server is trusted
            hexa = ssh_get_hexa(hash, hlen);
            fprintf(stderr, "Public key hash: %s\n", hexa);
            fprintf(stderr,"The server is unknown. Do you trust the host key? [yes/no] :");
            free(hexa);
            if (fgets(buf, sizeof(buf), stdin) == NULL) {
                free(hash);
                return -1;
            }
            if (strncasecmp(buf, "yes", 3) != 0) {
                free(hash);
                return -1;
            }
            if (ssh_write_knownhost(session) < 0) {
                fprintf(stderr, "Error %s\n", strerror(errno));
                free(hash);
                return -1;
            }
            break;

        case SSH_SERVER_ERROR:
            fprintf(stderr, "Error %s", ssh_get_error(session));
            free(hash);
            return -1;
    }

    free(hash);
    return 0;
}

// Creates an SSH channel in the SSH session, and forward the connection to the REMOTE_HOST
ssh_channel open_ssh_tunnel(ssh_session session, 
            const char* destination_host, int destination_port) {
    ssh_channel channel;
    int rc;
    char buffer[256];
    unsigned int nbytes;

    channel = ssh_channel_new(session); // Init channel
    if (channel == NULL)
        return NULL;

    rc = channel_open_forward(channel,
                            destination_host, destination_port,
                            LOCALHOST, LOCALPORT); // Forward the channel to the REMOTE_HOST
    if (rc != SSH_OK){
        fprintf(stderr, "Error %s", ssh_get_error(session));
        ssh_channel_free(channel);
        return NULL;
    }

    return channel;
}

// Close the channel
int close_ssh_tunnel(ssh_channel channel) {
    ssh_channel_send_eof(channel);
    ssh_channel_close(channel);
    ssh_channel_free(channel);

    return SSH_OK;
}

// Open a local port such that the client and the echo server can communicate through the SSH tunnel
// This function will also create a thread which will listen for connection in the localport
int open_local_port(ssh_session session, pthread_t *thread) {

    int optval = 1, n = -1, on = 1;
    struct sockaddr_in addr;
    struct tunnel_t *tunnelinfo;

    pthread_attr_t attr;

    // Init socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if ( sock == -1 ) {
        fprintf(stderr, "failed to create socket\n");
        return -1;
    }
    
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *)&optval, sizeof(optval)); 
    
    // Make the sock nonblocking 
    int rc = ioctl(sock, FIONBIO, (char *)&on);
    if (rc < 0) {
        perror("ioctl() failed");
        close(sock);
        return -1;
    }

    // Bind the socket
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_addr.s_addr = inet_addr(LOCALHOST);
    addr.sin_port = htons(LOCALPORT);

    rc = bind(sock,(struct sockaddr *)&addr, sizeof(addr));
    if ( rc == -1 ) {
        perror("bind failed");
        close(sock);
        return -1;
    }
    
    // Listen on the port with a backlog of 5
    listen(sock, 5);

    // Init the tunnel_t structure 
    tunnelinfo = (struct tunnel_t *)malloc(sizeof(struct tunnel_t));
    tunnelinfo->sockdesc = sock;
    tunnelinfo->session  = session;

    // Set thread attr as joinable
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    // create the thread
    rc = pthread_create(thread, &attr, listen_on_local_port, (void *)tunnelinfo);
    pthread_attr_destroy(&attr);    

    if (rc) {
        close(sock);
        fprintf(stderr, "failed to create thread\n");
        return -1;
    }

    return rc;
}

// This is the thread function, basically listen on the localport for connection
// On a new connection it create a new SSH channel  
void *listen_on_local_port(void *argv) {

    struct tunnel_t *tunnelinfo;
    int sock, newsock;
    char buff[BUFFER_SIZE];
    int readlen = 0, rc;

    tunnelinfo = (struct tunnel_t *) argv;
    sock = tunnelinfo->sockdesc;
    ssh_session session = tunnelinfo->session;

    ssh_channel channel;

    // Init the pollfd
    struct pollfd fds[3];
    int timeout;
    int current_size, nfds = 1, end_server = FALSE;

    memset(fds, 0 , sizeof(fds));
    
    fds[0].fd = sock;
    fds[0].events = POLLIN;

    timeout = (3 * 60 * 1000);

    printf("waiting for new connection...\n");
    do {
        rc = poll(fds, nfds, timeout); // Polling for socket to be readable  

        if (rc < 0) {
            perror("poll() failed");
            break;
        } 
        
        if (rc == 0) {
            fprintf(stderr, "poll() timed out.  End program.\n");
            break;
        }

        current_size = nfds;
        int i;
        for (i = 0; i < current_size; i++) {
            
            if(fds[i].revents == 0)
                continue;
            
            if(fds[i].revents != POLLIN) {
                fprintf(stderr, "error! revents = %d\n", fds[i].revents);
                end_server = TRUE;
                break;

            }
            if (fds[i].fd == sock) { // On new connection 
                printf("new connection in the localport\n");
                
                if (current_size == 3) {
                    fprintf(stderr, "only 1 connection is allowed in this demo\n");
                    continue;
                }

                struct sockaddr_in client; 
                int addrlen = sizeof(client); 
                newsock = accept(sock, (struct sockaddr *) &client, &addrlen); // Accept the connection
                if (newsock < 0) {
                    if (errno != EWOULDBLOCK) {
                        perror("accept() failed");
                        end_server = TRUE;
                    }
                    break;
                }
                 
                fds[nfds].fd = newsock; // Populate the new client socket for polling 
                fds[nfds].events = POLLIN;
                nfds++;
                
                printf("spawning a new tunnel...\n");
                channel = open_ssh_tunnel(session, REMOTE_HOST, REMOTE_PORT); // Open a ssh tunnel

                if(channel == NULL) {
                    fprintf(stderr, "error in opening SSH channel\n");
                    end_server = TRUE;
                    break;
                }

                // Populate the SSH session socket for polling, 
                // so that response in the ssh socket can be received 
                fds[nfds].fd = ssh_get_fd(session);  
                fds[nfds].events = POLLIN;
                nfds++;
            } else if (fds[i].fd == newsock) { // If the client socket is readable 

                int bytecount = 0;
                do {

                    readlen = 0;
                    memset(buff, 0, BUFFER_SIZE);
                    
                    // read the line socket 
                    if ( (readlen = recv (newsock, buff, BUFFER_SIZE, 0)) < 0 ) {
                        
                        // If any error other than EWOULDBLOCK we will close the connection
                        if( readlen != EWOULDBLOCK ) {
                            perror("recv() failed");
                            end_server = TRUE;
                        }
                        break;
                    }

                    if( readlen == 0 ) {
                        printf("client connection closed\n");
                        end_server = TRUE;
                        break;
                    }

                    bytecount += readlen;
                    // write into the SSH socket
                    if ( ssh_channel_write (channel, buff, readlen) == SSH_ERROR ) {
                        fprintf(stderr, "error writing into channel\n");
                        end_server = TRUE;
                        break;
                    }
                } while (readlen == BUFFER_SIZE);

                printf("bytes received = %d\n", bytecount);
                if(end_server == TRUE) {
                    break;
                } 

            } else { // If the SSH channel is readable 

                int bytecount = 0;
                do {

                    readlen = 0;
                    int cpoll = channel_poll(channel, 0); // Poll the channel for data

                    if(cpoll == SSH_ERROR) {
                        fprintf(stderr, "error in polling channel\n");
                        end_server = TRUE;
                        break;
                    }

                    if(cpoll == 0 ) {
                        printf("remote server connection closed\n");
                        end_server = TRUE;
                        break;
                    }
                    ssh_buffer ssh_buff = buffer_new(); // Init a new buffer for data

                    // Read data back from the SSH channel
                    if ( (readlen = channel_read_buffer ( channel, ssh_buff, BUFFER_SIZE, 0 ) ) == SSH_ERROR ) {
                        fprintf(stderr, "error reading from channel\n");
                        end_server = TRUE;
                        break;
                    }
                    if (readlen == 0) {
                        break;
                    }

                    char *content = ( char * ) buffer_get ( ssh_buff );
                    readlen = buffer_get_len(ssh_buff);
                    bytecount += readlen;
                    
                    // Write the data back into the client socket 
                    if ( send (newsock, content, readlen, 0 ) < 0) {
                        perror("send() failed");
                        end_server = TRUE;
                        break;
                    }
                    buffer_free(ssh_buff); // Free the buffer
                } while (readlen == BUFFER_SIZE);
                
                printf("bytes sent = %d\n", bytecount);
                if( end_server == TRUE) {
                    break;
                }                
            }
        }
    } while ( end_server != TRUE);

    // Deinitilize the resources 
    close_ssh_tunnel(channel);
    close(newsock);
    close(sock);
    free(tunnelinfo);
    
    rc = end_server ? EXIT_FAILURE : EXIT_SUCCESS;
    pthread_exit((void *)&rc); // Exit thread 
}
