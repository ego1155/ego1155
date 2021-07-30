# Install script for directory: /Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys/src

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

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Library/Developer/CommandLineTools/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xCorex" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/macosx/libplibsys.0.dylib")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsys.0.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsys.0.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "/usr/local/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsys.0.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/strip" -x "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsys.0.dylib")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xCorex" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/macosx/libplibsys.dylib")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsys.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsys.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "/usr/local/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsys.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/strip" -x "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsys.dylib")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/macosx/libplibsysstatic.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsysstatic.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsysstatic.a")
    execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsysstatic.a")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/macosx/libplibsys.0.dylib")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsys.0.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsys.0.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "/usr/local/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsys.0.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/strip" -x "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsys.0.dylib")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/macosx/libplibsys.dylib")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsys.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsys.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "/usr/local/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsys.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/strip" -x "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsys.dylib")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xCorex" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/macosx/libplibsysstatic.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsysstatic.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsysstatic.a")
    execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsysstatic.a")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xCorex" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/plibsys" TYPE FILE FILES
    "/Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys/src/patomic.h"
    "/Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys/src/ptypes.h"
    "/Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys/src/pmacros.h"
    "/Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys/src/pmacroscompiler.h"
    "/Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys/src/pmacroscpu.h"
    "/Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys/src/pmacrosos.h"
    "/Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys/src/pcondvariable.h"
    "/Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys/src/pcryptohash.h"
    "/Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys/src/perror.h"
    "/Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys/src/perrortypes.h"
    "/Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys/src/pdir.h"
    "/Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys/src/pfile.h"
    "/Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys/src/phashtable.h"
    "/Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys/src/pinifile.h"
    "/Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys/src/plibsys.h"
    "/Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys/src/plibraryloader.h"
    "/Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys/src/plist.h"
    "/Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys/src/pmain.h"
    "/Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys/src/pmem.h"
    "/Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys/src/pmutex.h"
    "/Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys/src/pprocess.h"
    "/Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys/src/prwlock.h"
    "/Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys/src/psemaphore.h"
    "/Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys/src/pshm.h"
    "/Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys/src/pshmbuffer.h"
    "/Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys/src/psocket.h"
    "/Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys/src/psocketaddress.h"
    "/Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys/src/pspinlock.h"
    "/Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys/src/pstdarg.h"
    "/Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys/src/pstring.h"
    "/Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys/src/ptimeprofiler.h"
    "/Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys/src/ptree.h"
    "/Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys/src/puthread.h"
    "/Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/macosx/plibsysconfig.h"
    )
endif()

