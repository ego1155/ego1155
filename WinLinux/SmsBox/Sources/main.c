#include "main.h"

SERVICE_STATUS ServiceStatus;
SERVICE_STATUS_HANDLE hStatus;
  
void ServiceMain(int argc, char** argv);
void ControlHandler(DWORD request);
int InitService();

const char* getFileNameFromPath(const char* path)
{
	char separator = '\\';
	if(path != NULL)
	{
		for(size_t i = strlen(path);  i > 0; --i)
		{
			if (path[i-1] == separator)
			{
				return &path[i];
			}
		}
	}
	return path;
}

char* getDirPathFromPath(char* path)
{
	char* parent = NULL;
    int parentLen;
    char* last = strrchr(path, '\\');

    if (last != NULL)
	{
		parentLen = strlen(path) - strlen(last + 1);
		parent = (char*)malloc(parentLen * sizeof(char));
        strncpy(parent, path, parentLen);
		parent[parentLen] = 0;
    }
	return parent;
}

char* exepath = NULL;
int timer = 0;

int WriteToLog(char* str)
{
	if (exepath == NULL)
		return -1;
	char* logName = (char*)malloc((strlen(exepath)+8) * sizeof(char));
	strcpy(logName, exepath);
	strcat(logName, "log.txt");
    FILE* log;
    log = fopen(logName, "a+");
	free(logName);
    if (log == NULL)
        return -1;
    fprintf(log, "%s\n", str);
    fclose(log);
    return 0;
}

void CronFunc(void)
{
	WriteToLog("CronFunc1 is running...\n");
}

int main(int argc, char *argv[])
{
	exepath = getDirPathFromPath(argv[0]);
	char* srvName = (char*)getFileNameFromPath(argv[0]);
	char* ext = strstr(srvName, ".exe");
	if (ext)
	{
		srvName[strlen(srvName) - 4] = 0;
	}
	char* srvDesc = srvName;
	
	if (argc == 2 && strcmp(argv[1], "ini") == 0)
	{
		char* iniName = (char*)malloc((strlen(srvName)+5) * sizeof(char));
		strcpy(iniName, srvName);
		strcat(iniName, ".ini");
		if( access( iniName, F_OK ) == -1)
		{
			ini_t* ini = ini_create(NULL);
			int section = ini_section_add( ini, srvName, 6 );
			ini_property_add( ini, section, "CronTab", 7, "60", 2 );
			ini_property_add( ini, section, "Enable", 6, "True", 4 );

			int size = ini_save( ini, NULL, 0 ); // Find the size needed
			char* data = (char*) malloc( size );
			size = ini_save( ini, data, size ); // Actually save the file
			ini_destroy( ini );

			FILE* fp = fopen( iniName, "w" );
			fwrite( data, 1, size, fp );
			fclose( fp );
			free( data );
		}
		free(iniName);
		return EXIT_SUCCESS;
	}
	
	char* cmd = (char*)malloc(1024 * sizeof(char));
	sprintf(cmd, "cmd /c sc query | find /I /C \"%s\"", srvName);
	char *hasSrv = exe_cmd(cmd);
	free(cmd);
	char* ret = strstr(hasSrv, "0");
	int isInst = (ret) ? 0 : 1;
	free(hasSrv);
	if (isInst == 0)
	{
		cmd = (char*)malloc(1024 * sizeof(char));
		sprintf(cmd, "cmd /c sc create %s binPath= \"%s srv\" DisplayName= \"%s \" start= auto", srvName, argv[0], srvName);
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
	
	if (exepath != NULL)
	{
		free(exepath);
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
			if (timer == 0)
			{
				const char* srvName = argv[0];
				int isSleep = 0;
				char* iniName = (char*)malloc((strlen(exepath)+strlen(srvName)+5) * sizeof(char));
				strcpy(iniName, exepath);
				strcat(iniName, srvName);
				strcat(iniName, ".ini");
				if( access( iniName, F_OK ) != -1)
				{
					FILE* fp = fopen( iniName, "r" );
					fseek( fp, 0, SEEK_END );
					int size = ftell( fp );
					fseek( fp, 0, SEEK_SET );
					char* data = (char*) malloc( size + 1 );
					fread( data, 1, size, fp );
					data[ size ] = '\0';
					fclose( fp );
					ini_t* ini = ini_load( data, NULL );
					free( data );
					
					int section, idx_c, idx_e;
					section = ini_find_section( ini, srvName, 6 );
					if (section != INI_NOT_FOUND)
					{
						idx_c = ini_find_property( ini, section, "CronTab", 7 );
						idx_e = ini_find_property( ini, section, "Enable", 6 );
						if (idx_c != INI_NOT_FOUND && idx_e != INI_NOT_FOUND)
						{
							char const* CronTab = ini_property_value( ini, section, idx_c );
							char const* Enable = ini_property_value( ini, section, idx_e );
							if (strcmp(Enable, "True") == 0)
							{
								int t = atoi(CronTab);
								if (t > 0)
								{
									timer = t;
								}
							}
							else
							{
								isSleep = 1;
							}
						}
						else
						{
							isSleep = 1;
						}
					}
					else
					{
						isSleep = 1;
					}
					
					ini_destroy( ini );
				}
				else
				{
					isSleep = 1;
				}
				free(iniName);
				
				if (isSleep == 1)
				{
					sleep(60);
				}
			}
			else
			{
				sleep(timer);
				CronFunc();
			}
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