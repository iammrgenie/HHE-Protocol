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
CMAKE_SOURCE_DIR = /home/mrgenie/Projects/HHE-Protocol

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mrgenie/Projects/HHE-Protocol/build

# Include any dependencies generated for this target.
include HHE/util/aes/CMakeFiles/aes.dir/depend.make

# Include the progress variables for this target.
include HHE/util/aes/CMakeFiles/aes.dir/progress.make

# Include the compile flags for this target's objects.
include HHE/util/aes/CMakeFiles/aes.dir/flags.make

HHE/util/aes/CMakeFiles/aes.dir/aes.cpp.o: HHE/util/aes/CMakeFiles/aes.dir/flags.make
HHE/util/aes/CMakeFiles/aes.dir/aes.cpp.o: ../HHE/util/aes/aes.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mrgenie/Projects/HHE-Protocol/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object HHE/util/aes/CMakeFiles/aes.dir/aes.cpp.o"
	cd /home/mrgenie/Projects/HHE-Protocol/build/HHE/util/aes && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/aes.dir/aes.cpp.o -c /home/mrgenie/Projects/HHE-Protocol/HHE/util/aes/aes.cpp

HHE/util/aes/CMakeFiles/aes.dir/aes.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aes.dir/aes.cpp.i"
	cd /home/mrgenie/Projects/HHE-Protocol/build/HHE/util/aes && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mrgenie/Projects/HHE-Protocol/HHE/util/aes/aes.cpp > CMakeFiles/aes.dir/aes.cpp.i

HHE/util/aes/CMakeFiles/aes.dir/aes.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aes.dir/aes.cpp.s"
	cd /home/mrgenie/Projects/HHE-Protocol/build/HHE/util/aes && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mrgenie/Projects/HHE-Protocol/HHE/util/aes/aes.cpp -o CMakeFiles/aes.dir/aes.cpp.s

HHE/util/aes/CMakeFiles/aes.dir/block.cpp.o: HHE/util/aes/CMakeFiles/aes.dir/flags.make
HHE/util/aes/CMakeFiles/aes.dir/block.cpp.o: ../HHE/util/aes/block.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mrgenie/Projects/HHE-Protocol/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object HHE/util/aes/CMakeFiles/aes.dir/block.cpp.o"
	cd /home/mrgenie/Projects/HHE-Protocol/build/HHE/util/aes && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/aes.dir/block.cpp.o -c /home/mrgenie/Projects/HHE-Protocol/HHE/util/aes/block.cpp

HHE/util/aes/CMakeFiles/aes.dir/block.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aes.dir/block.cpp.i"
	cd /home/mrgenie/Projects/HHE-Protocol/build/HHE/util/aes && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mrgenie/Projects/HHE-Protocol/HHE/util/aes/block.cpp > CMakeFiles/aes.dir/block.cpp.i

HHE/util/aes/CMakeFiles/aes.dir/block.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aes.dir/block.cpp.s"
	cd /home/mrgenie/Projects/HHE-Protocol/build/HHE/util/aes && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mrgenie/Projects/HHE-Protocol/HHE/util/aes/block.cpp -o CMakeFiles/aes.dir/block.cpp.s

# Object files for target aes
aes_OBJECTS = \
"CMakeFiles/aes.dir/aes.cpp.o" \
"CMakeFiles/aes.dir/block.cpp.o"

# External object files for target aes
aes_EXTERNAL_OBJECTS =

HHE/util/aes/libaes.a: HHE/util/aes/CMakeFiles/aes.dir/aes.cpp.o
HHE/util/aes/libaes.a: HHE/util/aes/CMakeFiles/aes.dir/block.cpp.o
HHE/util/aes/libaes.a: HHE/util/aes/CMakeFiles/aes.dir/build.make
HHE/util/aes/libaes.a: HHE/util/aes/CMakeFiles/aes.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mrgenie/Projects/HHE-Protocol/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libaes.a"
	cd /home/mrgenie/Projects/HHE-Protocol/build/HHE/util/aes && $(CMAKE_COMMAND) -P CMakeFiles/aes.dir/cmake_clean_target.cmake
	cd /home/mrgenie/Projects/HHE-Protocol/build/HHE/util/aes && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/aes.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
HHE/util/aes/CMakeFiles/aes.dir/build: HHE/util/aes/libaes.a

.PHONY : HHE/util/aes/CMakeFiles/aes.dir/build

HHE/util/aes/CMakeFiles/aes.dir/clean:
	cd /home/mrgenie/Projects/HHE-Protocol/build/HHE/util/aes && $(CMAKE_COMMAND) -P CMakeFiles/aes.dir/cmake_clean.cmake
.PHONY : HHE/util/aes/CMakeFiles/aes.dir/clean

HHE/util/aes/CMakeFiles/aes.dir/depend:
	cd /home/mrgenie/Projects/HHE-Protocol/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mrgenie/Projects/HHE-Protocol /home/mrgenie/Projects/HHE-Protocol/HHE/util/aes /home/mrgenie/Projects/HHE-Protocol/build /home/mrgenie/Projects/HHE-Protocol/build/HHE/util/aes /home/mrgenie/Projects/HHE-Protocol/build/HHE/util/aes/CMakeFiles/aes.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : HHE/util/aes/CMakeFiles/aes.dir/depend

