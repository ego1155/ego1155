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
include tests/CMakeFiles/pshmbuffer_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/CMakeFiles/pshmbuffer_test.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/pshmbuffer_test.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/pshmbuffer_test.dir/flags.make

tests/CMakeFiles/pshmbuffer_test.dir/pshmbuffer_test.cpp.o: tests/CMakeFiles/pshmbuffer_test.dir/flags.make
tests/CMakeFiles/pshmbuffer_test.dir/pshmbuffer_test.cpp.o: /Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys/tests/pshmbuffer_test.cpp
tests/CMakeFiles/pshmbuffer_test.dir/pshmbuffer_test.cpp.o: tests/CMakeFiles/pshmbuffer_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/macosx/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/pshmbuffer_test.dir/pshmbuffer_test.cpp.o"
	cd /Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/macosx/tests && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/pshmbuffer_test.dir/pshmbuffer_test.cpp.o -MF CMakeFiles/pshmbuffer_test.dir/pshmbuffer_test.cpp.o.d -o CMakeFiles/pshmbuffer_test.dir/pshmbuffer_test.cpp.o -c /Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys/tests/pshmbuffer_test.cpp

tests/CMakeFiles/pshmbuffer_test.dir/pshmbuffer_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pshmbuffer_test.dir/pshmbuffer_test.cpp.i"
	cd /Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/macosx/tests && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys/tests/pshmbuffer_test.cpp > CMakeFiles/pshmbuffer_test.dir/pshmbuffer_test.cpp.i

tests/CMakeFiles/pshmbuffer_test.dir/pshmbuffer_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pshmbuffer_test.dir/pshmbuffer_test.cpp.s"
	cd /Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/macosx/tests && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys/tests/pshmbuffer_test.cpp -o CMakeFiles/pshmbuffer_test.dir/pshmbuffer_test.cpp.s

# Object files for target pshmbuffer_test
pshmbuffer_test_OBJECTS = \
"CMakeFiles/pshmbuffer_test.dir/pshmbuffer_test.cpp.o"

# External object files for target pshmbuffer_test
pshmbuffer_test_EXTERNAL_OBJECTS =

pshmbuffer_test: tests/CMakeFiles/pshmbuffer_test.dir/pshmbuffer_test.cpp.o
pshmbuffer_test: tests/CMakeFiles/pshmbuffer_test.dir/build.make
pshmbuffer_test: libplibsys.0.dylib
pshmbuffer_test: tests/CMakeFiles/pshmbuffer_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/macosx/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../pshmbuffer_test"
	cd /Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/macosx/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pshmbuffer_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/pshmbuffer_test.dir/build: pshmbuffer_test
.PHONY : tests/CMakeFiles/pshmbuffer_test.dir/build

tests/CMakeFiles/pshmbuffer_test.dir/clean:
	cd /Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/macosx/tests && $(CMAKE_COMMAND) -P CMakeFiles/pshmbuffer_test.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/pshmbuffer_test.dir/clean

tests/CMakeFiles/pshmbuffer_test.dir/depend:
	cd /Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/macosx && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys /Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys/tests /Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/macosx /Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/macosx/tests /Users/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/macosx/tests/CMakeFiles/pshmbuffer_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/pshmbuffer_test.dir/depend

