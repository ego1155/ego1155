#include "main.h"

SERVICE_STATUS ServiceStatus;
SERVICE_STATUS_HANDLE hStatus;
  
void ServiceMain(int argc, char** argv);
void ControlHandler(DWORD request);
int InitService();

int WriteToLog(char* str)
{
    FILE* log;
    log = fopen(LOGFILE, "a+");
    if (log == NULL)
        return -1;
    fprintf(log, "%s\n", str);
    fclose(log);
    return 0;
}

int main(int argc, char *argv[])
{
	char *result = exe_cmd("dir");
	printf("adafasfdasdf %zu\n", strlen(result));
	fwrite(result, 1, strlen(result), stdout);
	free(result);
	  
	return EXIT_SUCCESS;
	
	
	SERVICE_TABLE_ENTRY ServiceTable[2];
    ServiceTable[0].lpServiceName = "SleepService";
	ServiceTable[0].lpServiceProc = (LPSERVICE_MAIN_FUNCTION)ServiceMain;
	ServiceTable[1].lpServiceName = NULL;
	ServiceTable[1].lpServiceProc = NULL;
	// Start the control dispatcher thread for our service
	StartServiceCtrlDispatcher(ServiceTable);
	
	(void)argc;
	(void)*argv;
	
	return EXIT_SUCCESS;
}

void ServiceMain(int argc, char** argv)
{
	int error;
	
	ServiceStatus.dwServiceType        = SERVICE_WIN32;
    ServiceStatus.dwCurrentState       = SERVICE_START_PENDING;
    ServiceStatus.dwControlsAccepted   = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;
    ServiceStatus.dwWin32ExitCode      = 0;
    ServiceStatus.dwServiceSpecificExitCode = 0;
    ServiceStatus.dwCheckPoint         = 0;
    ServiceStatus.dwWaitHint           = 0;
	
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
		ServiceStatus.dwCurrentState       = SERVICE_STOPPED;
        ServiceStatus.dwWin32ExitCode      = -1;
        SetServiceStatus(hStatus, &ServiceStatus);
        return;
    }
    // We report the running status to SCM.
    ServiceStatus.dwCurrentState = SERVICE_RUNNING;
    SetServiceStatus (hStatus, &ServiceStatus);

    // The worker loop of a service
    while (ServiceStatus.dwCurrentState == SERVICE_RUNNING)
    {
        /* Do nothing but loop once every 5 minutes */
        while(1)
        {
            sleep(300);
			WriteToLog("Running....");
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
    return(result);
}

// Control handler function
void ControlHandler(DWORD request)
{
    switch(request)
    {
        case SERVICE_CONTROL_STOP:
			WriteToLog("Monitoring stopped.");
 
			ServiceStatus.dwWin32ExitCode = 0;
            ServiceStatus.dwCurrentState  = SERVICE_STOPPED;
            SetServiceStatus (hStatus, &ServiceStatus);
            return;

        case SERVICE_CONTROL_SHUTDOWN:
            WriteToLog("Monitoring stopped.");
 
			ServiceStatus.dwWin32ExitCode = 0;
            ServiceStatus.dwCurrentState  = SERVICE_STOPPED;
            SetServiceStatus (hStatus, &ServiceStatus);
            return;

        default:
			break;
	}

    // Report current status
    SetServiceStatus (hStatus,  &ServiceStatus);

    return;
}