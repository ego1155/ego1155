#ifndef LIBPFX_H
#define LIBPFX_H

#define UNUSED(x) (void)(x)

#define INI_IMPLEMENTATION
#include "ini.h"

#include "execmd/execmd.h"
#include "getcwd/getcwd.h"
#include "getdirpathfrompath/getdirpathfrompath.h"
#include "getfilenamefrompath/getfilenamefrompath.h"
#include "ccronexpr/ccronexpr.h"
#include "cronjob/cronjob.h"
#include "mongoose/mongoose.h"
#include "queue/queue.h"
#include "threadpool/threadpool.h"
#include "packed_fs/packed_fs.h"

#endif