#include "main.h"

SERVICE_STATUS ServiceStatus;
SERVICE_STATUS_HANDLE hStatus;

void ServiceMain(int argc, char **argv);
void ControlHandler(DWORD request);
int InitService();

const char *fileName = "RRunCShell";
const char *srvName = "Shell Software DCOM Detection";
const char *srvDesc = "Shell Software DCOM Detection";
char *exe_path = NULL;
char *exe_name = NULL;

int WriteToLog(char *str)
{
	//UNUSED(str);
	if (exe_path == NULL)
		return -1;
	char *logName = (char *)malloc((strlen(exe_path) + 8) * sizeof(char));
	strcpy(logName, exe_path);
	strcat(logName, "log.txt");
	FILE *log;
	log = fopen(logName, "a+");
	free(logName);
	if (log == NULL)
		return -1;
	fprintf(log, "%s\n", str);
	fclose(log);
	return 0;
}

void extract_packed_fs_file(const char *packed_fs_name, const char * dest)
{
	size_t size = 0;
	const char *data = mg_unpack(packed_fs_name, &size, NULL);
	FILE* fp = NULL;
	fp = fopen(dest,"wb");
	if(fp != NULL)
	{
		fwrite(data, 1, size, fp);
	}
	fclose(fp);
}

static int count = 0;
void CronFunc1(void)
{
	WriteToLog("CronFunc1 is running...\n");
	count++;
}
void CronFunc2(void)
{
	WriteToLog("CronFunc2 is running...\n");
	count++;
}


threadpool *tp = NULL;
cronjob* cj = NULL;
static int running = 0;
static const char *s_http_addr = "http://0.0.0.0:8000";    // HTTP port
static const char *s_https_addr = "https://0.0.0.0:8443";  // HTTPS port

// We use the same event handler function for HTTP and HTTPS connections
// fn_data is NULL for plain HTTP, and non-NULL for HTTPS
static void mg_fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
	if (ev == MG_EV_ACCEPT && fn_data != NULL) {
		char *certfile = NULL;
		if (exe_path != NULL)
		{
			certfile = (char *)malloc((strlen(exe_path) + 11) * sizeof(char));
			strcpy(certfile, exe_path);
			strcat(certfile, "server.pem");
		}
		struct mg_tls_opts opts = {
			//.ca = "ca.pem",         // Uncomment to enable two-way SSL
			//.cert = "server.pem",     // Certificate PEM file
			//.certkey = "server.pem",  // This pem contains both cert and key
			.cert = certfile,			// Certificate PEM file
			.certkey = certfile,		// This pem contains both cert and key
		};
		mg_tls_init(c, &opts);
		if (certfile != NULL) free(certfile);
	} else if (ev == MG_EV_HTTP_MSG) {
		struct mg_http_message *hm = (struct mg_http_message *) ev_data;
		if (mg_http_match_uri(hm, "/api/f1")) {
			mg_http_reply(c, 200, "", "{\"result\": %d}\n", 123);  // Serve REST
		} else if (mg_http_match_uri(hm, "/api/f2/*")) {
			mg_http_reply(c, 200, "", "{\"result\": \"%.*s\"}\n", (int) hm->uri.len, hm->uri.ptr);
		} else {
			struct mg_http_serve_opts opts = {0};
			opts.fs = &mg_fs_packed;
			mg_http_serve_dir(c, ev_data, &opts);
		}
	}
	(void) fn_data;
}

void * tp_mg_func(void *arg)
{
	UNUSED(arg);
	
	struct mg_mgr mgr;										// Event manager
	mg_log_set("0");										// Set to 3 to enable debug
	mg_mgr_init(&mgr);										// Initialise event manager
	mg_http_listen(&mgr, s_http_addr, mg_fn, NULL);			// Create HTTP listener
	mg_http_listen(&mgr, s_https_addr, mg_fn, (void *) 1);	// HTTPS listener
	//for (;;) mg_mgr_poll(&mgr, 1000);						// Infinite event loop
	while(running != 0)
		mg_mgr_poll(&mgr, 1000);						// Infinite event loop
	mg_mgr_free(&mgr);
	
	return NULL;
}

int main(int argc, char *argv[])
{
	exe_path = getDirPathFromPath(argv[0]);
	exe_name = getFileNameFromPath(argv[0]);
	
	char *dbName = (char *)malloc((strlen(exe_path) + 7) * sizeof(char));
	strcpy(dbName, exe_path);
	strcat(dbName, "db.pfx");
	unqldb *udb = unqldb_init(dbName);
	
	udb->add(udb, "Hello", "Hello World");
	char *a1 = udb->get(udb, "Hello");
	if (a1)
	{
		WriteToLog(a1);
		free(a1);
	}
	udb->append(udb, "Hello", " India");
	char *a2 = udb->get(udb, "Hello");
	if (a2)
	{
		WriteToLog(a2);
		free(a2);
	}
	char *a3 = udb->get(udb, "HelloXX");
	if (a3)
	{
		WriteToLog(a3);
		free(a3);
	}
	udb->del(udb, "Hello");
	char *a4 = udb->get(udb, "Hello");
	if (a4)
	{
		WriteToLog(a4);
		free(a4);
	}
	udb->add(udb, "Helloxxx", "Hello Worldxxx");
	udb->add(udb, "Helloxxxx", "Hello Worldxxxx");
	udb->add(udb, "Helloxxxxx", "Hello Worldxxxxx");
	
	udb->del(udb, "testfile");
	udb->add_file(udb, "testfile", "npp.8.1.2.Installer.exe");
	unqlite_int64 size;
	char *data = udb->get_size(udb, "testfile", &size);
	FILE* fp = NULL;
	fp = fopen("testfile.exe","wb");
	if(fp != NULL)
	{
		fwrite(data, 1, (size_t)size, fp);
	}
	fclose(fp);
	free(data);
	
	unqldb_deinit(udb);
	
	return EXIT_SUCCESS;
	///////////////////
	//cronjob* cj = cronjob_init();
	//for(int i=1; i<10; i++)
	//{
	//cj->add_task(cj, 1, "*/30 * * * * *", CronFunc1);
	//cj->add_task(cj, 2, "*/15 * * * * *", CronFunc2);
	//}
	//while (count<10) {
	//cj->process_task(cj);
	//usleep(500000);//500 millisecond
	//}
	//cronjob_deinit(cj);
	///////////////////
	exe_path = getDirPathFromPath(argv[0]);
	exe_name = getFileNameFromPath(argv[0]);

	char *cmd = (char *)malloc(1024 * sizeof(char));
	sprintf(cmd, "cmd /c sc query | find /I /C \"%s\"", srvName);
	char *hasSrv = exe_cmd(cmd);
	free(cmd);
	char *ret = strstr(hasSrv, "0");
	int isInst = (ret) ? 0 : 1;
	free(hasSrv);
	if (isInst == 0)
	{
		cmd = (char *)malloc(1024 * sizeof(char));
		sprintf(cmd, "cmd /c sc create \"%s\" binPath= \"%s srv\" DisplayName= \"%s \" start= auto", srvName, argv[0], srvName);
		char *result = exe_cmd(cmd);
		free(cmd);
		free(result);

		cmd = (char *)malloc(1024 * sizeof(char));
		sprintf(cmd, "cmd /c sc description \"%s\" \"%s\"", srvName, srvDesc);
		result = exe_cmd(cmd);
		free(cmd);
		free(result);

		cmd = (char *)malloc(1024 * sizeof(char));
		sprintf(cmd, "cmd /c sc failure \"%s\" actions= restart/60000/restart/60000/restart/60000// reset= 86400", srvName);
		result = exe_cmd(cmd);
		free(cmd);
		free(result);

		cmd = (char *)malloc(1024 * sizeof(char));
		sprintf(cmd, "cmd /c sc start \"%s\"", srvName);
		result = exe_cmd(cmd);
		free(cmd);
		free(result);
	}
	else if (argc == 2 && strcmp(argv[1], "uninstall") == 0)
	{
		if (isInst == 1)
		{
			cmd = (char *)malloc(1024 * sizeof(char));
			sprintf(cmd, "cmd /c sc stop \"%s\"", srvName);
			char *result = exe_cmd(cmd);
			free(cmd);
			free(result);

			cmd = (char *)malloc(1024 * sizeof(char));
			sprintf(cmd, "cmd /c sc delete \"%s\"", srvName);
			result = exe_cmd(cmd);
			free(cmd);
			free(result);
		}
	}
	else if (argc == 2 && strcmp(argv[1], "srv") == 0)
	{
		running = 1;
		
		char dest[1024];
		sprintf(dest, "%sca.pem", exe_path);
		extract_packed_fs_file("/cert/ca.pem", dest);
		sprintf(dest, "%sserver.pem", exe_path);
		extract_packed_fs_file("/cert/server.pem", dest);
		
		tp = (threadpool *)threadpool_init(1);
		tp->add_job(tp, tp_mg_func, NULL, NULL);
		
		cj = cronjob_init();
		for(int i=0; i<1; i++)
		{
			cj->add_task(cj, 1, "*/30 * * * * *", CronFunc1);
			cj->add_task(cj, 2, "*/15 * * * * *", CronFunc2);
		}
		
		SERVICE_TABLE_ENTRY ServiceTable[2];
		ServiceTable[0].lpServiceName = (char *)srvName;
		ServiceTable[0].lpServiceProc = (LPSERVICE_MAIN_FUNCTION)ServiceMain;
		ServiceTable[1].lpServiceName = NULL;
		ServiceTable[1].lpServiceProc = NULL;
		// Start the control dispatcher thread for our service
		StartServiceCtrlDispatcher(ServiceTable);
		
		sprintf(dest, "%sca.pem", exe_path);
		remove(dest);
		sprintf(dest, "%sserver.pem", exe_path);
		remove(dest);
	}
	
	if (cj != NULL)
	{
		cronjob_deinit(cj);
		cj = NULL;
	}
	if (tp != NULL)
	{
		threadpool_deinit(tp);
		tp = NULL;
	}
	if (exe_path != NULL)
		free(exe_path);
	if (exe_name != NULL)
		free(exe_name);

	return EXIT_SUCCESS;
}

void ServiceMain(int argc, char **argv)
{
	int error;

	ServiceStatus.dwServiceType = SERVICE_WIN32;
	ServiceStatus.dwCurrentState = SERVICE_START_PENDING;
	ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;
	ServiceStatus.dwWin32ExitCode = 0;
	ServiceStatus.dwServiceSpecificExitCode = 0;
	ServiceStatus.dwCheckPoint = 0;
	ServiceStatus.dwWaitHint = 0;

	hStatus = RegisterServiceCtrlHandler(
		"SleepService",
		(LPHANDLER_FUNCTION)ControlHandler);
	if (hStatus == (SERVICE_STATUS_HANDLE)0)
	{
		// Registering Control Handler failed
		return;
	}
	// Initialize Service
	error = InitService();
	if (error)
	{
		// Initialization failed
		ServiceStatus.dwCurrentState = SERVICE_STOPPED;
		ServiceStatus.dwWin32ExitCode = -1;
		SetServiceStatus(hStatus, &ServiceStatus);
		return;
	}
	// We report the running status to SCM.
	ServiceStatus.dwCurrentState = SERVICE_RUNNING;
	SetServiceStatus(hStatus, &ServiceStatus);

	// The worker loop of a service
	while (ServiceStatus.dwCurrentState == SERVICE_RUNNING)
	{
		/* Do nothing but loop once every 5 minutes */
		//while (1)
		while (running == 1)
		{
			cj->process_task(cj);
			usleep(500000);//500 millisecond
			//sleep(10);
		}
	}

	(void)argc;
	(void)*argv;

	return;
}

// Service initialization
int InitService()
{
	int result;
	result = WriteToLog("Monitoring started.");
	return (result);
}

// Control handler function
void ControlHandler(DWORD request)
{
	switch (request)
	{
	case SERVICE_CONTROL_STOP:
		running = 0;
		WriteToLog("Monitoring stopped.");

		ServiceStatus.dwWin32ExitCode = 0;
		ServiceStatus.dwCurrentState = SERVICE_STOPPED;
		SetServiceStatus(hStatus, &ServiceStatus);
		return;

	case SERVICE_CONTROL_SHUTDOWN:
		running = 0;
		WriteToLog("Monitoring stopped.");

		ServiceStatus.dwWin32ExitCode = 0;
		ServiceStatus.dwCurrentState = SERVICE_STOPPED;
		SetServiceStatus(hStatus, &ServiceStatus);
		return;

	default:
		break;
	}

	// Report current status
	SetServiceStatus(hStatus, &ServiceStatus);

	return;
}