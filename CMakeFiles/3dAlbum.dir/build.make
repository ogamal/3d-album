# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.3

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
CMAKE_COMMAND = /opt/local/bin/cmake

# The command to remove a file.
RM = /opt/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/iOsama/Code/cpp/album

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/iOsama/Code/cpp/album

# Include any dependencies generated for this target.
include CMakeFiles/3dAlbum.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/3dAlbum.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/3dAlbum.dir/flags.make

CMakeFiles/3dAlbum.dir/app.cpp.o: CMakeFiles/3dAlbum.dir/flags.make
CMakeFiles/3dAlbum.dir/app.cpp.o: app.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/iOsama/Code/cpp/album/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/3dAlbum.dir/app.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/3dAlbum.dir/app.cpp.o -c /Users/iOsama/Code/cpp/album/app.cpp

CMakeFiles/3dAlbum.dir/app.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/3dAlbum.dir/app.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/iOsama/Code/cpp/album/app.cpp > CMakeFiles/3dAlbum.dir/app.cpp.i

CMakeFiles/3dAlbum.dir/app.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/3dAlbum.dir/app.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/iOsama/Code/cpp/album/app.cpp -o CMakeFiles/3dAlbum.dir/app.cpp.s

CMakeFiles/3dAlbum.dir/app.cpp.o.requires:

.PHONY : CMakeFiles/3dAlbum.dir/app.cpp.o.requires

CMakeFiles/3dAlbum.dir/app.cpp.o.provides: CMakeFiles/3dAlbum.dir/app.cpp.o.requires
	$(MAKE) -f CMakeFiles/3dAlbum.dir/build.make CMakeFiles/3dAlbum.dir/app.cpp.o.provides.build
.PHONY : CMakeFiles/3dAlbum.dir/app.cpp.o.provides

CMakeFiles/3dAlbum.dir/app.cpp.o.provides.build: CMakeFiles/3dAlbum.dir/app.cpp.o


CMakeFiles/3dAlbum.dir/main.cpp.o: CMakeFiles/3dAlbum.dir/flags.make
CMakeFiles/3dAlbum.dir/main.cpp.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/iOsama/Code/cpp/album/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/3dAlbum.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/3dAlbum.dir/main.cpp.o -c /Users/iOsama/Code/cpp/album/main.cpp

CMakeFiles/3dAlbum.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/3dAlbum.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/iOsama/Code/cpp/album/main.cpp > CMakeFiles/3dAlbum.dir/main.cpp.i

CMakeFiles/3dAlbum.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/3dAlbum.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/iOsama/Code/cpp/album/main.cpp -o CMakeFiles/3dAlbum.dir/main.cpp.s

CMakeFiles/3dAlbum.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/3dAlbum.dir/main.cpp.o.requires

CMakeFiles/3dAlbum.dir/main.cpp.o.provides: CMakeFiles/3dAlbum.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/3dAlbum.dir/build.make CMakeFiles/3dAlbum.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/3dAlbum.dir/main.cpp.o.provides

CMakeFiles/3dAlbum.dir/main.cpp.o.provides.build: CMakeFiles/3dAlbum.dir/main.cpp.o


# Object files for target 3dAlbum
3dAlbum_OBJECTS = \
"CMakeFiles/3dAlbum.dir/app.cpp.o" \
"CMakeFiles/3dAlbum.dir/main.cpp.o"

# External object files for target 3dAlbum
3dAlbum_EXTERNAL_OBJECTS =

3dAlbum: CMakeFiles/3dAlbum.dir/app.cpp.o
3dAlbum: CMakeFiles/3dAlbum.dir/main.cpp.o
3dAlbum: CMakeFiles/3dAlbum.dir/build.make
3dAlbum: CMakeFiles/3dAlbum.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/iOsama/Code/cpp/album/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable 3dAlbum"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/3dAlbum.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/3dAlbum.dir/build: 3dAlbum

.PHONY : CMakeFiles/3dAlbum.dir/build

CMakeFiles/3dAlbum.dir/requires: CMakeFiles/3dAlbum.dir/app.cpp.o.requires
CMakeFiles/3dAlbum.dir/requires: CMakeFiles/3dAlbum.dir/main.cpp.o.requires

.PHONY : CMakeFiles/3dAlbum.dir/requires

CMakeFiles/3dAlbum.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/3dAlbum.dir/cmake_clean.cmake
.PHONY : CMakeFiles/3dAlbum.dir/clean

CMakeFiles/3dAlbum.dir/depend:
	cd /Users/iOsama/Code/cpp/album && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/iOsama/Code/cpp/album /Users/iOsama/Code/cpp/album /Users/iOsama/Code/cpp/album /Users/iOsama/Code/cpp/album /Users/iOsama/Code/cpp/album/CMakeFiles/3dAlbum.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/3dAlbum.dir/depend

