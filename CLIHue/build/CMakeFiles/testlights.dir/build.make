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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/rowan/Documents/GitHub/Philpis-Hue-Desktop-Gui/CLIHue

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rowan/Documents/GitHub/Philpis-Hue-Desktop-Gui/CLIHue/build

# Include any dependencies generated for this target.
include CMakeFiles/testlights.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/testlights.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/testlights.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/testlights.dir/flags.make

CMakeFiles/testlights.dir/testlights.cpp.o: CMakeFiles/testlights.dir/flags.make
CMakeFiles/testlights.dir/testlights.cpp.o: ../testlights.cpp
CMakeFiles/testlights.dir/testlights.cpp.o: CMakeFiles/testlights.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rowan/Documents/GitHub/Philpis-Hue-Desktop-Gui/CLIHue/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/testlights.dir/testlights.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/testlights.dir/testlights.cpp.o -MF CMakeFiles/testlights.dir/testlights.cpp.o.d -o CMakeFiles/testlights.dir/testlights.cpp.o -c /home/rowan/Documents/GitHub/Philpis-Hue-Desktop-Gui/CLIHue/testlights.cpp

CMakeFiles/testlights.dir/testlights.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testlights.dir/testlights.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rowan/Documents/GitHub/Philpis-Hue-Desktop-Gui/CLIHue/testlights.cpp > CMakeFiles/testlights.dir/testlights.cpp.i

CMakeFiles/testlights.dir/testlights.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testlights.dir/testlights.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rowan/Documents/GitHub/Philpis-Hue-Desktop-Gui/CLIHue/testlights.cpp -o CMakeFiles/testlights.dir/testlights.cpp.s

# Object files for target testlights
testlights_OBJECTS = \
"CMakeFiles/testlights.dir/testlights.cpp.o"

# External object files for target testlights
testlights_EXTERNAL_OBJECTS =

testlights: CMakeFiles/testlights.dir/testlights.cpp.o
testlights: CMakeFiles/testlights.dir/build.make
testlights: CMakeFiles/testlights.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/rowan/Documents/GitHub/Philpis-Hue-Desktop-Gui/CLIHue/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable testlights"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testlights.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/testlights.dir/build: testlights
.PHONY : CMakeFiles/testlights.dir/build

CMakeFiles/testlights.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/testlights.dir/cmake_clean.cmake
.PHONY : CMakeFiles/testlights.dir/clean

CMakeFiles/testlights.dir/depend:
	cd /home/rowan/Documents/GitHub/Philpis-Hue-Desktop-Gui/CLIHue/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rowan/Documents/GitHub/Philpis-Hue-Desktop-Gui/CLIHue /home/rowan/Documents/GitHub/Philpis-Hue-Desktop-Gui/CLIHue /home/rowan/Documents/GitHub/Philpis-Hue-Desktop-Gui/CLIHue/build /home/rowan/Documents/GitHub/Philpis-Hue-Desktop-Gui/CLIHue/build /home/rowan/Documents/GitHub/Philpis-Hue-Desktop-Gui/CLIHue/build/CMakeFiles/testlights.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/testlights.dir/depend

