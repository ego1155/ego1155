#include <microhttpd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <libssh2.h>
#include "ezini.h"
#include "opener.h"

#define PAGE "<html><head><title>libmicrohttpd demo</title>"\
             "</head><body>libmicrohttpd demo</body></html>"

static enum MHD_Result
ahc_echo(void * cls,
         struct MHD_Connection * connection,
         const char * url,
         const char * method,
         const char * version,
         const char * upload_data,
         size_t * upload_data_size,
         void ** ptr) {
  static int dummy;
  const char * page = cls;
  struct MHD_Response * response;
  int ret;

  if (0 != strcmp(method, "GET"))
    return MHD_NO; /* unexpected method */
  if (&dummy != *ptr)
    {
      /* The first time only the headers are valid,
         do not respond in the first round... */
      *ptr = &dummy;
      return MHD_YES;
    }
  if (0 != *upload_data_size)
    return MHD_NO; /* upload data in a GET!? */
  *ptr = NULL; /* clear context pointer */
  response = MHD_create_response_from_buffer (strlen(page),
                                              (void*) page,
  					      MHD_RESPMEM_PERSISTENT);
  ret = MHD_queue_response(connection,
			   MHD_HTTP_OK,
			   response);
  MHD_destroy_response(response);
  return ret;
}

int main()
{
	ini_entry_list_t list;
	list = NULL;
    AddEntryToList(&list, "SecureTcp", "Ssh_Server_Id", "sshuser");
	AddEntryToList(&list, "SecureTcp", "Ssh_Server_Host", "");
	AddEntryToList(&list, "SecureTcp", "Ssh_Server_Port", "");
	AddEntryToList(&list, "SecureTcp", "Ssh_Mapping_Host", "localhost");
	AddEntryToList(&list, "SecureTcp", "Rdp", "False");
	AddEntryToList(&list, "SecureTcp", "Rfp", "False");
	
	AddEntryToList(&list, "Rdp Name", "Rdp_UserName", "");
	AddEntryToList(&list, "Rdp Name", "Rdp_Password", "");
	AddEntryToList(&list, "Rdp Name", "Rdp_Server_Host", "");
	AddEntryToList(&list, "Rdp Name", "Rdp_Server_Port", "3389");
	AddEntryToList(&list, "Rdp Name", "Rdp_Mapping_Port", "5000");
	AddEntryToList(&list, "Rdp Name", "Rdp_Auto_Login", "False");
	AddEntryToList(&list, "Rdp Name", "Enable", "False");
	
	AddEntryToList(&list, "Rfp Name", "Rfp_Server_Host", "");
	AddEntryToList(&list, "Rfp Name", "Rfp_Server_Port", "3389");
	AddEntryToList(&list, "Rfp Name", "Rfp_Mapping_Port", "5000");
	AddEntryToList(&list, "Rfp Name", "Enable", "False");
    
	if (MakeINIFile("SecureTcp.ini", list) != 0)
    {
		return 1;
    }
    FreeList(list);
	
	LIBSSH2_SESSION *session;
	LIBSSH2_LISTENER *listener = NULL;
	LIBSSH2_CHANNEL *channel = NULL;
	int rc = libssh2_init(0);
	if(rc != 0) {
        	fprintf(stderr, "libssh2 initialization failed (%d)\n", rc);
        	return 1;
	}
	session = libssh2_session_init();
#ifdef _WIN64
	printf("\nSecureTcp Win64\n\n");
#elif __APPLE__
	printf("\nSecureTcp MacOsX\n\n");
#elif __linux
	printf("\nSecureTcp Linux\n\n");
#elif __unix
	printf("\nSecureTcp Unix\n\n");
#elif __posix
	printf("\nSecureTcp Posix\n\n");
#endif
	printf("\nSecureTcp\n\n");
	libssh2_session_free(session);
	libssh2_exit();
	
	struct MHD_Daemon * d;
  d = MHD_start_daemon(MHD_USE_THREAD_PER_CONNECTION,
		       9999,
		       NULL,
		       NULL,
		       &ahc_echo,
		       PAGE,
		       MHD_OPTION_END);
  if (d == NULL)
    return 1;
	opener("http://127.0.0.1:9999");
  (void) getc (stdin);
  MHD_stop_daemon(d);
  
	return 0;
}
