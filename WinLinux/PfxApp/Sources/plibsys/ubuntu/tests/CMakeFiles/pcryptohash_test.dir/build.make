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
CMAKE_SOURCE_DIR = /home/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/ubuntu

# Include any dependencies generated for this target.
include tests/CMakeFiles/pcryptohash_test.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/pcryptohash_test.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/pcryptohash_test.dir/flags.make

tests/CMakeFiles/pcryptohash_test.dir/pcryptohash_test.cpp.o: tests/CMakeFiles/pcryptohash_test.dir/flags.make
tests/CMakeFiles/pcryptohash_test.dir/pcryptohash_test.cpp.o: /home/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys/tests/pcryptohash_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/ubuntu/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/pcryptohash_test.dir/pcryptohash_test.cpp.o"
	cd /home/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/ubuntu/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pcryptohash_test.dir/pcryptohash_test.cpp.o -c /home/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys/tests/pcryptohash_test.cpp

tests/CMakeFiles/pcryptohash_test.dir/pcryptohash_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pcryptohash_test.dir/pcryptohash_test.cpp.i"
	cd /home/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/ubuntu/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys/tests/pcryptohash_test.cpp > CMakeFiles/pcryptohash_test.dir/pcryptohash_test.cpp.i

tests/CMakeFiles/pcryptohash_test.dir/pcryptohash_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pcryptohash_test.dir/pcryptohash_test.cpp.s"
	cd /home/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/ubuntu/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys/tests/pcryptohash_test.cpp -o CMakeFiles/pcryptohash_test.dir/pcryptohash_test.cpp.s

# Object files for target pcryptohash_test
pcryptohash_test_OBJECTS = \
"CMakeFiles/pcryptohash_test.dir/pcryptohash_test.cpp.o"

# External object files for target pcryptohash_test
pcryptohash_test_EXTERNAL_OBJECTS =

pcryptohash_test: tests/CMakeFiles/pcryptohash_test.dir/pcryptohash_test.cpp.o
pcryptohash_test: tests/CMakeFiles/pcryptohash_test.dir/build.make
pcryptohash_test: libplibsys.so.0
pcryptohash_test: tests/CMakeFiles/pcryptohash_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/ubuntu/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../pcryptohash_test"
	cd /home/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/ubuntu/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pcryptohash_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/pcryptohash_test.dir/build: pcryptohash_test

.PHONY : tests/CMakeFiles/pcryptohash_test.dir/build

tests/CMakeFiles/pcryptohash_test.dir/clean:
	cd /home/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/ubuntu/tests && $(CMAKE_COMMAND) -P CMakeFiles/pcryptohash_test.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/pcryptohash_test.dir/clean

tests/CMakeFiles/pcryptohash_test.dir/depend:
	cd /home/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/ubuntu && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys /home/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/plibsys/tests /home/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/ubuntu /home/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/ubuntu/tests /home/nilesh/Desktop/ego1155/WinLinux/PfxApp/Sources/plibsys/ubuntu/tests/CMakeFiles/pcryptohash_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/pcryptohash_test.dir/depend

