# CMAKE generated file: DO NOT EDIT!
# Generated by "MSYS Makefiles" Generator, CMake Version 3.21

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /C/msys64/mingw64/bin/cmake.exe

# The command to remove a file.
RM = /C/msys64/mingw64/bin/cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /C/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/plibsys

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /C/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/window

# Include any dependencies generated for this target.
include tests/CMakeFiles/psemaphore_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/CMakeFiles/psemaphore_test.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/psemaphore_test.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/psemaphore_test.dir/flags.make

tests/CMakeFiles/psemaphore_test.dir/psemaphore_test.cpp.obj: tests/CMakeFiles/psemaphore_test.dir/flags.make
tests/CMakeFiles/psemaphore_test.dir/psemaphore_test.cpp.obj: C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/plibsys/tests/psemaphore_test.cpp
tests/CMakeFiles/psemaphore_test.dir/psemaphore_test.cpp.obj: tests/CMakeFiles/psemaphore_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/C/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/window/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/psemaphore_test.dir/psemaphore_test.cpp.obj"
	cd /C/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/window/tests && /C/msys64/mingw64/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/psemaphore_test.dir/psemaphore_test.cpp.obj -MF CMakeFiles/psemaphore_test.dir/psemaphore_test.cpp.obj.d -o CMakeFiles/psemaphore_test.dir/psemaphore_test.cpp.obj -c /C/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/plibsys/tests/psemaphore_test.cpp

tests/CMakeFiles/psemaphore_test.dir/psemaphore_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/psemaphore_test.dir/psemaphore_test.cpp.i"
	cd /C/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/window/tests && /C/msys64/mingw64/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /C/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/plibsys/tests/psemaphore_test.cpp > CMakeFiles/psemaphore_test.dir/psemaphore_test.cpp.i

tests/CMakeFiles/psemaphore_test.dir/psemaphore_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/psemaphore_test.dir/psemaphore_test.cpp.s"
	cd /C/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/window/tests && /C/msys64/mingw64/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /C/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/plibsys/tests/psemaphore_test.cpp -o CMakeFiles/psemaphore_test.dir/psemaphore_test.cpp.s

# Object files for target psemaphore_test
psemaphore_test_OBJECTS = \
"CMakeFiles/psemaphore_test.dir/psemaphore_test.cpp.obj"

# External object files for target psemaphore_test
psemaphore_test_EXTERNAL_OBJECTS =

psemaphore_test.exe: tests/CMakeFiles/psemaphore_test.dir/psemaphore_test.cpp.obj
psemaphore_test.exe: tests/CMakeFiles/psemaphore_test.dir/build.make
psemaphore_test.exe: libplibsys.dll.a
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/C/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/window/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../psemaphore_test.exe"
	cd /C/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/window/tests && /C/msys64/mingw64/bin/cmake.exe -E rm -f CMakeFiles/psemaphore_test.dir/objects.a
	cd /C/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/window/tests && /C/msys64/mingw64/bin/ar.exe qc CMakeFiles/psemaphore_test.dir/objects.a $(psemaphore_test_OBJECTS) $(psemaphore_test_EXTERNAL_OBJECTS)
	cd /C/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/window/tests && /C/msys64/mingw64/bin/g++.exe -O3 -DNDEBUG -Wl,--whole-archive CMakeFiles/psemaphore_test.dir/objects.a -Wl,--no-whole-archive -o ../psemaphore_test.exe -Wl,--out-implib,libpsemaphore_test.dll.a -Wl,--major-image-version,0,--minor-image-version,0  ../libplibsys.dll.a -lws2_32 -lkernel32 -luser32 -lgdi32 -lwinspool -lshell32 -lole32 -loleaut32 -luuid -lcomdlg32 -ladvapi32 

# Rule to build all files generated by this target.
tests/CMakeFiles/psemaphore_test.dir/build: psemaphore_test.exe
.PHONY : tests/CMakeFiles/psemaphore_test.dir/build

tests/CMakeFiles/psemaphore_test.dir/clean:
	cd /C/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/window/tests && $(CMAKE_COMMAND) -P CMakeFiles/psemaphore_test.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/psemaphore_test.dir/clean

tests/CMakeFiles/psemaphore_test.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MSYS Makefiles" /C/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/plibsys /C/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/plibsys/tests /C/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/window /C/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/window/tests /C/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/window/tests/CMakeFiles/psemaphore_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/psemaphore_test.dir/depend

