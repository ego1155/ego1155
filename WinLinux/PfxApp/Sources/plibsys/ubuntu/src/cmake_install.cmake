# Install script for directory: /home/nilesh/Desktop/plibsys/plibsys/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xCorex" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsys.so.0" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsys.so.0")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsys.so.0"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/nilesh/Desktop/plibsys/ubuntu/libplibsys.so.0")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsys.so.0" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsys.so.0")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsys.so.0")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xCorex" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsys.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsys.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsys.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/nilesh/Desktop/plibsys/ubuntu/libplibsys.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsys.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsys.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsys.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/nilesh/Desktop/plibsys/ubuntu/libplibsysstatic.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsys.so.0" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsys.so.0")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsys.so.0"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/nilesh/Desktop/plibsys/ubuntu/libplibsys.so.0")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsys.so.0" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsys.so.0")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsys.so.0")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsys.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsys.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsys.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/nilesh/Desktop/plibsys/ubuntu/libplibsys.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsys.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsys.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsys.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xCorex" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/nilesh/Desktop/plibsys/ubuntu/libplibsysstatic.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xCorex" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/plibsys" TYPE FILE FILES
    "/home/nilesh/Desktop/plibsys/plibsys/src/patomic.h"
    "/home/nilesh/Desktop/plibsys/plibsys/src/ptypes.h"
    "/home/nilesh/Desktop/plibsys/plibsys/src/pmacros.h"
    "/home/nilesh/Desktop/plibsys/plibsys/src/pmacroscompiler.h"
    "/home/nilesh/Desktop/plibsys/plibsys/src/pmacroscpu.h"
    "/home/nilesh/Desktop/plibsys/plibsys/src/pmacrosos.h"
    "/home/nilesh/Desktop/plibsys/plibsys/src/pcondvariable.h"
    "/home/nilesh/Desktop/plibsys/plibsys/src/pcryptohash.h"
    "/home/nilesh/Desktop/plibsys/plibsys/src/perror.h"
    "/home/nilesh/Desktop/plibsys/plibsys/src/perrortypes.h"
    "/home/nilesh/Desktop/plibsys/plibsys/src/pdir.h"
    "/home/nilesh/Desktop/plibsys/plibsys/src/pfile.h"
    "/home/nilesh/Desktop/plibsys/plibsys/src/phashtable.h"
    "/home/nilesh/Desktop/plibsys/plibsys/src/pinifile.h"
    "/home/nilesh/Desktop/plibsys/plibsys/src/plibsys.h"
    "/home/nilesh/Desktop/plibsys/plibsys/src/plibraryloader.h"
    "/home/nilesh/Desktop/plibsys/plibsys/src/plist.h"
    "/home/nilesh/Desktop/plibsys/plibsys/src/pmain.h"
    "/home/nilesh/Desktop/plibsys/plibsys/src/pmem.h"
    "/home/nilesh/Desktop/plibsys/plibsys/src/pmutex.h"
    "/home/nilesh/Desktop/plibsys/plibsys/src/pprocess.h"
    "/home/nilesh/Desktop/plibsys/plibsys/src/prwlock.h"
    "/home/nilesh/Desktop/plibsys/plibsys/src/psemaphore.h"
    "/home/nilesh/Desktop/plibsys/plibsys/src/pshm.h"
    "/home/nilesh/Desktop/plibsys/plibsys/src/pshmbuffer.h"
    "/home/nilesh/Desktop/plibsys/plibsys/src/psocket.h"
    "/home/nilesh/Desktop/plibsys/plibsys/src/psocketaddress.h"
    "/home/nilesh/Desktop/plibsys/plibsys/src/pspinlock.h"
    "/home/nilesh/Desktop/plibsys/plibsys/src/pstdarg.h"
    "/home/nilesh/Desktop/plibsys/plibsys/src/pstring.h"
    "/home/nilesh/Desktop/plibsys/plibsys/src/ptimeprofiler.h"
    "/home/nilesh/Desktop/plibsys/plibsys/src/ptree.h"
    "/home/nilesh/Desktop/plibsys/plibsys/src/puthread.h"
    "/home/nilesh/Desktop/plibsys/ubuntu/plibsysconfig.h"
    )
endif()

