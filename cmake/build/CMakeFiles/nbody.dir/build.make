# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sami/git/nbody

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sami/git/nbody/cmake/build

# Include any dependencies generated for this target.
include CMakeFiles/nbody.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/nbody.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/nbody.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/nbody.dir/flags.make

CMakeFiles/nbody.dir/codegen:
.PHONY : CMakeFiles/nbody.dir/codegen

CMakeFiles/nbody.dir/nbody.c.o: CMakeFiles/nbody.dir/flags.make
CMakeFiles/nbody.dir/nbody.c.o: /home/sami/git/nbody/nbody.c
CMakeFiles/nbody.dir/nbody.c.o: CMakeFiles/nbody.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/sami/git/nbody/cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/nbody.dir/nbody.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/nbody.dir/nbody.c.o -MF CMakeFiles/nbody.dir/nbody.c.o.d -o CMakeFiles/nbody.dir/nbody.c.o -c /home/sami/git/nbody/nbody.c

CMakeFiles/nbody.dir/nbody.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/nbody.dir/nbody.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/sami/git/nbody/nbody.c > CMakeFiles/nbody.dir/nbody.c.i

CMakeFiles/nbody.dir/nbody.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/nbody.dir/nbody.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/sami/git/nbody/nbody.c -o CMakeFiles/nbody.dir/nbody.c.s

# Object files for target nbody
nbody_OBJECTS = \
"CMakeFiles/nbody.dir/nbody.c.o"

# External object files for target nbody
nbody_EXTERNAL_OBJECTS =

/home/sami/git/nbody/lib/libnbody.so: CMakeFiles/nbody.dir/nbody.c.o
/home/sami/git/nbody/lib/libnbody.so: CMakeFiles/nbody.dir/build.make
/home/sami/git/nbody/lib/libnbody.so: CMakeFiles/nbody.dir/compiler_depend.ts
/home/sami/git/nbody/lib/libnbody.so: CMakeFiles/nbody.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/sami/git/nbody/cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C shared library /home/sami/git/nbody/lib/libnbody.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/nbody.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/nbody.dir/build: /home/sami/git/nbody/lib/libnbody.so
.PHONY : CMakeFiles/nbody.dir/build

CMakeFiles/nbody.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/nbody.dir/cmake_clean.cmake
.PHONY : CMakeFiles/nbody.dir/clean

CMakeFiles/nbody.dir/depend:
	cd /home/sami/git/nbody/cmake/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sami/git/nbody /home/sami/git/nbody /home/sami/git/nbody/cmake/build /home/sami/git/nbody/cmake/build /home/sami/git/nbody/cmake/build/CMakeFiles/nbody.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/nbody.dir/depend

