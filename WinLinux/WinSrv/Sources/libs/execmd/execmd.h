#ifndef EXECMD_H
#define EXECMD_H

#ifdef __unix__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#elif _WIN32

#include <windows.h>

#endif

char *exe_cmd(const char *cmd);

#endif