# Install script for directory: C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/plibsys/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/plibsys")
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
  set(CMAKE_OBJDUMP "C:/msys64/mingw64/bin/objdump.exe")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/window/libplibsys.dll.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xCorex" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/window/libplibsys.dll")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsys.dll" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsys.dll")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "C:/msys64/mingw64/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsys.dll")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/window/libplibsysstatic.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/window/libplibsys.dll.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/window/libplibsys.dll")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsys.dll" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsys.dll")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "C:/msys64/mingw64/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsys.dll")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/window/libplibsysstatic.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xCorex" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/window/libplibsys.dll.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/window/libplibsys.dll")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsys.dll" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsys.dll")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "C:/msys64/mingw64/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplibsys.dll")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xCorex" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/window/libplibsysstatic.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xCorex" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/plibsys" TYPE FILE FILES
    "C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/plibsys/src/patomic.h"
    "C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/plibsys/src/ptypes.h"
    "C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/plibsys/src/pmacros.h"
    "C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/plibsys/src/pmacroscompiler.h"
    "C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/plibsys/src/pmacroscpu.h"
    "C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/plibsys/src/pmacrosos.h"
    "C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/plibsys/src/pcondvariable.h"
    "C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/plibsys/src/pcryptohash.h"
    "C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/plibsys/src/perror.h"
    "C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/plibsys/src/perrortypes.h"
    "C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/plibsys/src/pdir.h"
    "C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/plibsys/src/pfile.h"
    "C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/plibsys/src/phashtable.h"
    "C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/plibsys/src/pinifile.h"
    "C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/plibsys/src/plibsys.h"
    "C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/plibsys/src/plibraryloader.h"
    "C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/plibsys/src/plist.h"
    "C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/plibsys/src/pmain.h"
    "C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/plibsys/src/pmem.h"
    "C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/plibsys/src/pmutex.h"
    "C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/plibsys/src/pprocess.h"
    "C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/plibsys/src/prwlock.h"
    "C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/plibsys/src/psemaphore.h"
    "C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/plibsys/src/pshm.h"
    "C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/plibsys/src/pshmbuffer.h"
    "C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/plibsys/src/psocket.h"
    "C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/plibsys/src/psocketaddress.h"
    "C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/plibsys/src/pspinlock.h"
    "C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/plibsys/src/pstdarg.h"
    "C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/plibsys/src/pstring.h"
    "C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/plibsys/src/ptimeprofiler.h"
    "C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/plibsys/src/ptree.h"
    "C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/plibsys/src/puthread.h"
    "C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/window/plibsysconfig.h"
    )
endif()

