#ifndef LIBPFX_H
#define LIBPFX_H

#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <libssh/libssh.h>
#include "../plibsys/plibsys/src/plibsys.h"

#define SC_LOG_PRINT_FILE_NAME
#include "sc_log/sc_log.h"

#define INI_IMPLEMENTATION
#include "ini.h"

#define STRPOOL_IMPLEMENTATION
#include "strpool.h"
#define ASSETSYS_IMPLEMENTATION
#include "assetsys.h"

#define CUTE_FILEWATCH_IMPLEMENTATION
#include "cute_filewatch.h"

#include "sc_str/sc_str.h"
#include "ccronexpr/ccronexpr.h"
#include "cronjob/cronjob.h"
#include "mongoose/mongoose.h"
#include "stripslash/stripslash.h"

#endif