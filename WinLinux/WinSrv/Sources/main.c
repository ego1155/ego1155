#include "main.h"

SERVICE_STATUS ServiceStatus;
SERVICE_STATUS_HANDLE hStatus;
  
void ServiceMain(int argc, char** argv);
void ControlHandler(DWORD request);
int InitService();

int WriteToLog(char* str)
{
    FILE* log;
    log = fopen("C:\\Users\\nilesh\\Desktop\\ego1155\\WinLinux\\WinSrv\\Output\\log.txt", "a+");
    if (log == NULL)
        return -1;
    fprintf(log, "%s\n", str);
    fclose(log);
    return 0;
}

int main(int argc, char *argv[])
{
	const char* srvName = "WinSrv";
	const char* srvDesc = "WinSrv";
	
	char* cmd = (char*)malloc(1024 * sizeof(char));
	sprintf(cmd, "cmd /c sc query | find /I /C \"%s\"", srvName);
	char *hasSrv = exe_cmd(cmd);
	free(cmd);
	char* ret = strstr(hasSrv, "0");
	int isInst = (ret) ? 0 : 1;
	free(hasSrv);
	if (isInst == 0)
	{
		//char *exec = get_cwd();
		//char* hasPath = strstr(argv[0], exec);
		//strcat(exec, "\\");
		//strcat(exec, argv[0]);
		cmd = (char*)malloc(1024 * sizeof(char));
		sprintf(cmd, "cmd /c sc create %s binPath= \"%s srv\" DisplayName= \"%s \" start= auto", srvName, argv[0], srvName);
		//free(exec);
		char *result = exe_cmd(cmd);
		free(cmd);
		free(result);
		
		cmd = (char*)malloc(1024 * sizeof(char));
		sprintf(cmd, "cmd /c sc description %s \"%s\"", srvName, srvDesc);
		result = exe_cmd(cmd);
		free(cmd);
		free(result);
		
		cmd = (char*)malloc(1024 * sizeof(char));
		sprintf(cmd, "cmd /c sc failure %s actions= restart/60000/restart/60000/restart/60000// reset= 86400", srvName);
		result = exe_cmd(cmd);
		free(cmd);
		free(result);
		
		cmd = (char*)malloc(1024 * sizeof(char));
		sprintf(cmd, "cmd /c sc start %s", srvName);
		result = exe_cmd(cmd);
		free(cmd);
		free(result);
	}
	else if (argc == 2 && strcmp(argv[1], "uninstall") == 0)
	{
		if (isInst == 1)
		{
			cmd = (char*)malloc(1024 * sizeof(char));
			sprintf(cmd, "cmd /c sc stop %s", srvName);
			char *result = exe_cmd(cmd);
			free(cmd);
			free(result);
			
			cmd = (char*)malloc(1024 * sizeof(char));
			sprintf(cmd, "cmd /c sc delete %s", srvName);
			result = exe_cmd(cmd);
			free(cmd);
			free(result);
		}
	}
	else if (argc == 2 && strcmp(argv[1], "srv") == 0)
	{
		SERVICE_TABLE_ENTRY ServiceTable[2];
		ServiceTable[0].lpServiceName = (char*)srvName;
		ServiceTable[0].lpServiceProc = (LPSERVICE_MAIN_FUNCTION)ServiceMain;
		ServiceTable[1].lpServiceName = NULL;
		ServiceTable[1].lpServiceProc = NULL;
		// Start the control dispatcher thread for our service
		StartServiceCtrlDispatcher(ServiceTable);
	}
	
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