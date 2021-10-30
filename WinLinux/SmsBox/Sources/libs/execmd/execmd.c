#include "execmd.h"

char *exe_cmd(const char *cmd)
{
	char *bfmout = NULL;
	
#ifdef __unix__

	FILE *fp = NULL;
	fp = popen(cmd, "r");
	if (!fp) {
		return bfmout;
	}
	
	char buffer[256];
	size_t bfread;
    size_t bfmalloc = 256;
    size_t bfmlen = 0;
    bfmout = malloc(bfmalloc);
	
	if (!bfmout) {
		return bfmout;
	}
	
	while ((bfread = fread(buffer, 1, sizeof(buffer), fp)) != 0) {
		if (bfmlen + bfread >= bfmalloc) {
			bfmalloc *= 2;
			bfmout = realloc(bfmout, bfmalloc);
		}
		memmove(bfmout + bfmlen, buffer, bfread);
		bfmlen += bfread;
	}
	pclose(fp);

#elif _WIN32

	// Create the read and write handles for stdout.
	HANDLE stdOutHandles[2];

	// Setup the security attributes.
	SECURITY_ATTRIBUTES saAttr;
	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES); 
	saAttr.bInheritHandle = TRUE; 
	saAttr.lpSecurityDescriptor = NULL; 

	// Create the pipe for stdout.
	if(!CreatePipe(&stdOutHandles[0], &stdOutHandles[1], &saAttr, 0))
		return bfmout;

	PROCESS_INFORMATION pInfo;
	ZeroMemory(&pInfo, sizeof(PROCESS_INFORMATION));

	// Specify the pipe handle and make sure the window is hidden.
	STARTUPINFO startInfo;
	ZeroMemory(&startInfo, sizeof(STARTUPINFO));
	startInfo.cb = sizeof(STARTUPINFO);
	startInfo.hStdOutput = stdOutHandles[1];
	startInfo.dwFlags |= STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
	startInfo.wShowWindow = SW_HIDE;

	// Call cscript.exe with slmgr.vbs -dlv as the parameters. Because of the nature of this command, I left the first parameter as NULL.
	//char expandedCScript[MAX_PATH];
	//ExpandEnvironmentStrings("%windir%\\System32\\cscript.exe //nologo \"%windir%\\System32\\slmgr.vbs\" -dlv", expandedCScript, MAX_PATH);
	if(!CreateProcess(NULL, (char *)cmd, NULL, NULL, TRUE, 0, NULL, NULL, &startInfo, &pInfo))
	{
		CloseHandle(stdOutHandles[0]);
		CloseHandle(stdOutHandles[1]);
		return bfmout;
	}

	// Wait for cscript.exe to exit.
	WaitForSingleObject(pInfo.hProcess, INFINITE);
	
	// Read the output from cscript.exe
	char buffer[2048];
	DWORD readBufferSize;
	
	BOOL result;
	if((result = ReadFile(stdOutHandles[0], buffer, 2048, &readBufferSize, NULL)))
	{
		// ReadFile does not null-terminate the buffer so we do that manually.
		buffer[readBufferSize] = '\0';

		// Display the output.
		//MessageBox(NULL, buffer, NULL, MB_OK);
		
		bfmout = malloc(2048);
		strcpy(bfmout, buffer);
	}

	// Close the handles.
	CloseHandle(stdOutHandles[0]);
	CloseHandle(stdOutHandles[1]);
	CloseHandle(pInfo.hProcess);
	CloseHandle(pInfo.hThread);

#endif
	
	return bfmout;
}