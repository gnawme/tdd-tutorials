# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_COMMAND = /home/norme/Programs/clion-2016.3.1/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/norme/Programs/clion-2016.3.1/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/norme/Projects/tdd-tutorials/goflist

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/norme/Projects/tdd-tutorials/goflist/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/goflist.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/goflist.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/goflist.dir/flags.make

CMakeFiles/goflist.dir/GoFListTest.cpp.o: CMakeFiles/goflist.dir/flags.make
CMakeFiles/goflist.dir/GoFListTest.cpp.o: ../GoFListTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/norme/Projects/tdd-tutorials/goflist/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/goflist.dir/GoFListTest.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/goflist.dir/GoFListTest.cpp.o -c /home/norme/Projects/tdd-tutorials/goflist/GoFListTest.cpp

CMakeFiles/goflist.dir/GoFListTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/goflist.dir/GoFListTest.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/norme/Projects/tdd-tutorials/goflist/GoFListTest.cpp > CMakeFiles/goflist.dir/GoFListTest.cpp.i

CMakeFiles/goflist.dir/GoFListTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/goflist.dir/GoFListTest.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/norme/Projects/tdd-tutorials/goflist/GoFListTest.cpp -o CMakeFiles/goflist.dir/GoFListTest.cpp.s

CMakeFiles/goflist.dir/GoFListTest.cpp.o.requires:

.PHONY : CMakeFiles/goflist.dir/GoFListTest.cpp.o.requires

CMakeFiles/goflist.dir/GoFListTest.cpp.o.provides: CMakeFiles/goflist.dir/GoFListTest.cpp.o.requires
	$(MAKE) -f CMakeFiles/goflist.dir/build.make CMakeFiles/goflist.dir/GoFListTest.cpp.o.provides.build
.PHONY : CMakeFiles/goflist.dir/GoFListTest.cpp.o.provides

CMakeFiles/goflist.dir/GoFListTest.cpp.o.provides.build: CMakeFiles/goflist.dir/GoFListTest.cpp.o


# Object files for target goflist
goflist_OBJECTS = \
"CMakeFiles/goflist.dir/GoFListTest.cpp.o"

# External object files for target goflist
goflist_EXTERNAL_OBJECTS =

goflist: CMakeFiles/goflist.dir/GoFListTest.cpp.o
goflist: CMakeFiles/goflist.dir/build.make
goflist: CMakeFiles/goflist.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/norme/Projects/tdd-tutorials/goflist/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable goflist"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/goflist.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/goflist.dir/build: goflist

.PHONY : CMakeFiles/goflist.dir/build

CMakeFiles/goflist.dir/requires: CMakeFiles/goflist.dir/GoFListTest.cpp.o.requires

.PHONY : CMakeFiles/goflist.dir/requires

CMakeFiles/goflist.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/goflist.dir/cmake_clean.cmake
.PHONY : CMakeFiles/goflist.dir/clean

CMakeFiles/goflist.dir/depend:
	cd /home/norme/Projects/tdd-tutorials/goflist/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/norme/Projects/tdd-tutorials/goflist /home/norme/Projects/tdd-tutorials/goflist /home/norme/Projects/tdd-tutorials/goflist/cmake-build-debug /home/norme/Projects/tdd-tutorials/goflist/cmake-build-debug /home/norme/Projects/tdd-tutorials/goflist/cmake-build-debug/CMakeFiles/goflist.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/goflist.dir/depend
