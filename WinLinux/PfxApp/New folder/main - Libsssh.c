#include "main.h"

int direct_forwarding(ssh_session session);

int main(int argc, char *argv[])
{
	int verbosity = SSH_LOG_PROTOCOL;
	int port = 22;
	
	ssh_session my_ssh_session;
	int rc;
  
	my_ssh_session = ssh_new();
	if (my_ssh_session == NULL)
		exit(-1);
	
	ssh_options_set(my_ssh_session, SSH_OPTIONS_HOST, "192.168.1.150");
	ssh_options_set(my_ssh_session, SSH_OPTIONS_PORT, &port);
	ssh_options_set(my_ssh_session, SSH_OPTIONS_USER, "hyundai");
	ssh_options_set(my_ssh_session, SSH_OPTIONS_LOG_VERBOSITY, &verbosity);
	
	rc = ssh_connect(my_ssh_session);
	if (rc != SSH_OK)
	{
		fprintf(stderr, "Error connecting to localhost: %s\n", ssh_get_error(my_ssh_session));
		ssh_free(my_ssh_session);
		exit(-1);
	}
	
	int auth = -1;
	ssh_key publicKey, privatekey;
	if(ssh_pki_import_pubkey_file("sshuser_public_key",&publicKey) == SSH_OK)
	{
		if(ssh_pki_import_privkey_file("sshuser_private_key",NULL,NULL,NULL,&privatekey) == SSH_OK)
		{
			auth = ssh_userauth_publickey(my_ssh_session, NULL, privatekey);
		}
    }
	if (auth != SSH_AUTH_SUCCESS)
	{
		fprintf(stderr, "Error authenticating to localhost: %s\n", ssh_get_error(my_ssh_session));
		ssh_disconnect(my_ssh_session);
		ssh_free(my_ssh_session);
		exit(-1);
	}
	
	printf("Successfully logon....");
	
	int res = direct_forwarding(my_ssh_session);
	if (res != SSH_OK)
	{
		fprintf(stderr, "Error direct_forwarding to localhost: %s\n", ssh_get_error(my_ssh_session));
		ssh_disconnect(my_ssh_session);
		ssh_free(my_ssh_session);
		exit(-1);
	}
	
	ssh_disconnect(my_ssh_session);
 	ssh_free(my_ssh_session);
  
	return 0;
}

int direct_forwarding(ssh_session session)
{
  ssh_channel forwarding_channel;
  int rc;
  char *http_get = "GET / HTTP/1.1\nHost: www.google.com\n\n";
  int nbytes, nwritten;
 
  forwarding_channel = ssh_channel_new(session);
  if (forwarding_channel == NULL) {
      return rc;
  }
 
  rc = ssh_channel_open_forward(forwarding_channel,
								"www.google.com", 80,
                                "localhost", 5000);
  if (rc != SSH_OK)
  {
    ssh_channel_free(forwarding_channel);
    return rc;
  }
 
  nbytes = strlen(http_get);
  nwritten = ssh_channel_write(forwarding_channel,
                           http_get,
                           nbytes);
  if (nbytes != nwritten)
  {
    ssh_channel_free(forwarding_channel);
    return SSH_ERROR;
  }
  
  /* char buffer[16384];
  int nbytes, nwritten;
  
	while (ssh_channel_is_open(forwarding_channel) && !ssh_channel_is_eof(forwarding_channel)) {
		if (!kbhit()) {
			  Sleep(100); // 0.05 second
		}
		nbytes = ssh_channel_read_nonblocking(forwarding_channel, buffer, sizeof(buffer), 0);
		if (nbytes < 0) return SSH_ERROR;
		if (nbytes > 0) {
			nwritten = write(1, buffer, nbytes);
			if (nwritten != nbytes) return SSH_ERROR;
			continue;
		}
		nbytes = read(0, buffer, sizeof(buffer));
		if (nbytes < 0) return SSH_ERROR;
		if (nbytes > 0) {
			nwritten = ssh_channel_write(forwarding_channel, buffer, nbytes);
			if (nwritten != nbytes) return SSH_ERROR;
		}
	} */
 
  ssh_channel_free(forwarding_channel);
  return SSH_OK;
}

