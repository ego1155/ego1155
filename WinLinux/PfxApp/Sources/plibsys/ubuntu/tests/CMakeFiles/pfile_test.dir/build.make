# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/nilesh/Desktop/plibsys/plibsys

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nilesh/Desktop/plibsys/ubuntu

# Include any dependencies generated for this target.
include tests/CMakeFiles/pfile_test.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/pfile_test.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/pfile_test.dir/flags.make

tests/CMakeFiles/pfile_test.dir/pfile_test.cpp.o: tests/CMakeFiles/pfile_test.dir/flags.make
tests/CMakeFiles/pfile_test.dir/pfile_test.cpp.o: /home/nilesh/Desktop/plibsys/plibsys/tests/pfile_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nilesh/Desktop/plibsys/ubuntu/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/pfile_test.dir/pfile_test.cpp.o"
	cd /home/nilesh/Desktop/plibsys/ubuntu/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pfile_test.dir/pfile_test.cpp.o -c /home/nilesh/Desktop/plibsys/plibsys/tests/pfile_test.cpp

tests/CMakeFiles/pfile_test.dir/pfile_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pfile_test.dir/pfile_test.cpp.i"
	cd /home/nilesh/Desktop/plibsys/ubuntu/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nilesh/Desktop/plibsys/plibsys/tests/pfile_test.cpp > CMakeFiles/pfile_test.dir/pfile_test.cpp.i

tests/CMakeFiles/pfile_test.dir/pfile_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pfile_test.dir/pfile_test.cpp.s"
	cd /home/nilesh/Desktop/plibsys/ubuntu/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nilesh/Desktop/plibsys/plibsys/tests/pfile_test.cpp -o CMakeFiles/pfile_test.dir/pfile_test.cpp.s

# Object files for target pfile_test
pfile_test_OBJECTS = \
"CMakeFiles/pfile_test.dir/pfile_test.cpp.o"

# External object files for target pfile_test
pfile_test_EXTERNAL_OBJECTS =

pfile_test: tests/CMakeFiles/pfile_test.dir/pfile_test.cpp.o
pfile_test: tests/CMakeFiles/pfile_test.dir/build.make
pfile_test: libplibsys.so.0
pfile_test: tests/CMakeFiles/pfile_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/nilesh/Desktop/plibsys/ubuntu/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../pfile_test"
	cd /home/nilesh/Desktop/plibsys/ubuntu/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pfile_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/pfile_test.dir/build: pfile_test

.PHONY : tests/CMakeFiles/pfile_test.dir/build

tests/CMakeFiles/pfile_test.dir/clean:
	cd /home/nilesh/Desktop/plibsys/ubuntu/tests && $(CMAKE_COMMAND) -P CMakeFiles/pfile_test.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/pfile_test.dir/clean

tests/CMakeFiles/pfile_test.dir/depend:
	cd /home/nilesh/Desktop/plibsys/ubuntu && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nilesh/Desktop/plibsys/plibsys /home/nilesh/Desktop/plibsys/plibsys/tests /home/nilesh/Desktop/plibsys/ubuntu /home/nilesh/Desktop/plibsys/ubuntu/tests /home/nilesh/Desktop/plibsys/ubuntu/tests/CMakeFiles/pfile_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/pfile_test.dir/depend

