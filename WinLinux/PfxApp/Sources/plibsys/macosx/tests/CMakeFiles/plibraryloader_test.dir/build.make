# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.21.1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.21.1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/macosx

# Include any dependencies generated for this target.
include tests/CMakeFiles/plibraryloader_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/CMakeFiles/plibraryloader_test.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/plibraryloader_test.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/plibraryloader_test.dir/flags.make

tests/CMakeFiles/plibraryloader_test.dir/plibraryloader_test.cpp.o: tests/CMakeFiles/plibraryloader_test.dir/flags.make
tests/CMakeFiles/plibraryloader_test.dir/plibraryloader_test.cpp.o: /Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys/tests/plibraryloader_test.cpp
tests/CMakeFiles/plibraryloader_test.dir/plibraryloader_test.cpp.o: tests/CMakeFiles/plibraryloader_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/macosx/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/plibraryloader_test.dir/plibraryloader_test.cpp.o"
	cd /Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/macosx/tests && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/plibraryloader_test.dir/plibraryloader_test.cpp.o -MF CMakeFiles/plibraryloader_test.dir/plibraryloader_test.cpp.o.d -o CMakeFiles/plibraryloader_test.dir/plibraryloader_test.cpp.o -c /Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys/tests/plibraryloader_test.cpp

tests/CMakeFiles/plibraryloader_test.dir/plibraryloader_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/plibraryloader_test.dir/plibraryloader_test.cpp.i"
	cd /Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/macosx/tests && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys/tests/plibraryloader_test.cpp > CMakeFiles/plibraryloader_test.dir/plibraryloader_test.cpp.i

tests/CMakeFiles/plibraryloader_test.dir/plibraryloader_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/plibraryloader_test.dir/plibraryloader_test.cpp.s"
	cd /Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/macosx/tests && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys/tests/plibraryloader_test.cpp -o CMakeFiles/plibraryloader_test.dir/plibraryloader_test.cpp.s

# Object files for target plibraryloader_test
plibraryloader_test_OBJECTS = \
"CMakeFiles/plibraryloader_test.dir/plibraryloader_test.cpp.o"

# External object files for target plibraryloader_test
plibraryloader_test_EXTERNAL_OBJECTS =

plibraryloader_test: tests/CMakeFiles/plibraryloader_test.dir/plibraryloader_test.cpp.o
plibraryloader_test: tests/CMakeFiles/plibraryloader_test.dir/build.make
plibraryloader_test: libplibsys.0.dylib
plibraryloader_test: tests/CMakeFiles/plibraryloader_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/macosx/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../plibraryloader_test"
	cd /Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/macosx/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/plibraryloader_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/plibraryloader_test.dir/build: plibraryloader_test
.PHONY : tests/CMakeFiles/plibraryloader_test.dir/build

tests/CMakeFiles/plibraryloader_test.dir/clean:
	cd /Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/macosx/tests && $(CMAKE_COMMAND) -P CMakeFiles/plibraryloader_test.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/plibraryloader_test.dir/clean

tests/CMakeFiles/plibraryloader_test.dir/depend:
	cd /Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/macosx && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys /Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys/tests /Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/macosx /Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/macosx/tests /Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/macosx/tests/CMakeFiles/plibraryloader_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/plibraryloader_test.dir/depend

