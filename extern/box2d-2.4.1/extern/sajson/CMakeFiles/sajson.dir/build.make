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
CMAKE_SOURCE_DIR = /home/matinr/CLionProjects/project-platformer-graverunner/extern/box2d-2.4.1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/matinr/CLionProjects/project-platformer-graverunner/extern/box2d-2.4.1

# Include any dependencies generated for this target.
include extern/sajson/CMakeFiles/sajson.dir/depend.make

# Include the progress variables for this target.
include extern/sajson/CMakeFiles/sajson.dir/progress.make

# Include the compile flags for this target's objects.
include extern/sajson/CMakeFiles/sajson.dir/flags.make

extern/sajson/CMakeFiles/sajson.dir/sajson.cpp.o: extern/sajson/CMakeFiles/sajson.dir/flags.make
extern/sajson/CMakeFiles/sajson.dir/sajson.cpp.o: extern/sajson/sajson.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/matinr/CLionProjects/project-platformer-graverunner/extern/box2d-2.4.1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object extern/sajson/CMakeFiles/sajson.dir/sajson.cpp.o"
	cd /home/matinr/CLionProjects/project-platformer-graverunner/extern/box2d-2.4.1/extern/sajson && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sajson.dir/sajson.cpp.o -c /home/matinr/CLionProjects/project-platformer-graverunner/extern/box2d-2.4.1/extern/sajson/sajson.cpp

extern/sajson/CMakeFiles/sajson.dir/sajson.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sajson.dir/sajson.cpp.i"
	cd /home/matinr/CLionProjects/project-platformer-graverunner/extern/box2d-2.4.1/extern/sajson && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/matinr/CLionProjects/project-platformer-graverunner/extern/box2d-2.4.1/extern/sajson/sajson.cpp > CMakeFiles/sajson.dir/sajson.cpp.i

extern/sajson/CMakeFiles/sajson.dir/sajson.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sajson.dir/sajson.cpp.s"
	cd /home/matinr/CLionProjects/project-platformer-graverunner/extern/box2d-2.4.1/extern/sajson && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/matinr/CLionProjects/project-platformer-graverunner/extern/box2d-2.4.1/extern/sajson/sajson.cpp -o CMakeFiles/sajson.dir/sajson.cpp.s

# Object files for target sajson
sajson_OBJECTS = \
"CMakeFiles/sajson.dir/sajson.cpp.o"

# External object files for target sajson
sajson_EXTERNAL_OBJECTS =

bin/libsajson.a: extern/sajson/CMakeFiles/sajson.dir/sajson.cpp.o
bin/libsajson.a: extern/sajson/CMakeFiles/sajson.dir/build.make
bin/libsajson.a: extern/sajson/CMakeFiles/sajson.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/matinr/CLionProjects/project-platformer-graverunner/extern/box2d-2.4.1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ../../bin/libsajson.a"
	cd /home/matinr/CLionProjects/project-platformer-graverunner/extern/box2d-2.4.1/extern/sajson && $(CMAKE_COMMAND) -P CMakeFiles/sajson.dir/cmake_clean_target.cmake
	cd /home/matinr/CLionProjects/project-platformer-graverunner/extern/box2d-2.4.1/extern/sajson && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sajson.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
extern/sajson/CMakeFiles/sajson.dir/build: bin/libsajson.a

.PHONY : extern/sajson/CMakeFiles/sajson.dir/build

extern/sajson/CMakeFiles/sajson.dir/clean:
	cd /home/matinr/CLionProjects/project-platformer-graverunner/extern/box2d-2.4.1/extern/sajson && $(CMAKE_COMMAND) -P CMakeFiles/sajson.dir/cmake_clean.cmake
.PHONY : extern/sajson/CMakeFiles/sajson.dir/clean

extern/sajson/CMakeFiles/sajson.dir/depend:
	cd /home/matinr/CLionProjects/project-platformer-graverunner/extern/box2d-2.4.1 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/matinr/CLionProjects/project-platformer-graverunner/extern/box2d-2.4.1 /home/matinr/CLionProjects/project-platformer-graverunner/extern/box2d-2.4.1/extern/sajson /home/matinr/CLionProjects/project-platformer-graverunner/extern/box2d-2.4.1 /home/matinr/CLionProjects/project-platformer-graverunner/extern/box2d-2.4.1/extern/sajson /home/matinr/CLionProjects/project-platformer-graverunner/extern/box2d-2.4.1/extern/sajson/CMakeFiles/sajson.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : extern/sajson/CMakeFiles/sajson.dir/depend

