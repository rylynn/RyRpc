# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.2

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.2.1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.2.1/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/rylynnxj/Development/ryrpc

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/rylynnxj/Development/ryrpc/build

# Include any dependencies generated for this target.
include CMakeFiles/test_svr.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test_svr.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_svr.dir/flags.make

CMakeFiles/test_svr.dir/main.cpp.o: CMakeFiles/test_svr.dir/flags.make
CMakeFiles/test_svr.dir/main.cpp.o: ../main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/rylynnxj/Development/ryrpc/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/test_svr.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/test_svr.dir/main.cpp.o -c /Users/rylynnxj/Development/ryrpc/main.cpp

CMakeFiles/test_svr.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_svr.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/rylynnxj/Development/ryrpc/main.cpp > CMakeFiles/test_svr.dir/main.cpp.i

CMakeFiles/test_svr.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_svr.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/rylynnxj/Development/ryrpc/main.cpp -o CMakeFiles/test_svr.dir/main.cpp.s

CMakeFiles/test_svr.dir/main.cpp.o.requires:
.PHONY : CMakeFiles/test_svr.dir/main.cpp.o.requires

CMakeFiles/test_svr.dir/main.cpp.o.provides: CMakeFiles/test_svr.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/test_svr.dir/build.make CMakeFiles/test_svr.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/test_svr.dir/main.cpp.o.provides

CMakeFiles/test_svr.dir/main.cpp.o.provides.build: CMakeFiles/test_svr.dir/main.cpp.o

CMakeFiles/test_svr.dir/net/poller.cpp.o: CMakeFiles/test_svr.dir/flags.make
CMakeFiles/test_svr.dir/net/poller.cpp.o: ../net/poller.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/rylynnxj/Development/ryrpc/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/test_svr.dir/net/poller.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/test_svr.dir/net/poller.cpp.o -c /Users/rylynnxj/Development/ryrpc/net/poller.cpp

CMakeFiles/test_svr.dir/net/poller.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_svr.dir/net/poller.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/rylynnxj/Development/ryrpc/net/poller.cpp > CMakeFiles/test_svr.dir/net/poller.cpp.i

CMakeFiles/test_svr.dir/net/poller.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_svr.dir/net/poller.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/rylynnxj/Development/ryrpc/net/poller.cpp -o CMakeFiles/test_svr.dir/net/poller.cpp.s

CMakeFiles/test_svr.dir/net/poller.cpp.o.requires:
.PHONY : CMakeFiles/test_svr.dir/net/poller.cpp.o.requires

CMakeFiles/test_svr.dir/net/poller.cpp.o.provides: CMakeFiles/test_svr.dir/net/poller.cpp.o.requires
	$(MAKE) -f CMakeFiles/test_svr.dir/build.make CMakeFiles/test_svr.dir/net/poller.cpp.o.provides.build
.PHONY : CMakeFiles/test_svr.dir/net/poller.cpp.o.provides

CMakeFiles/test_svr.dir/net/poller.cpp.o.provides.build: CMakeFiles/test_svr.dir/net/poller.cpp.o

CMakeFiles/test_svr.dir/net/event_manage.cpp.o: CMakeFiles/test_svr.dir/flags.make
CMakeFiles/test_svr.dir/net/event_manage.cpp.o: ../net/event_manage.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/rylynnxj/Development/ryrpc/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/test_svr.dir/net/event_manage.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/test_svr.dir/net/event_manage.cpp.o -c /Users/rylynnxj/Development/ryrpc/net/event_manage.cpp

CMakeFiles/test_svr.dir/net/event_manage.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_svr.dir/net/event_manage.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/rylynnxj/Development/ryrpc/net/event_manage.cpp > CMakeFiles/test_svr.dir/net/event_manage.cpp.i

CMakeFiles/test_svr.dir/net/event_manage.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_svr.dir/net/event_manage.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/rylynnxj/Development/ryrpc/net/event_manage.cpp -o CMakeFiles/test_svr.dir/net/event_manage.cpp.s

CMakeFiles/test_svr.dir/net/event_manage.cpp.o.requires:
.PHONY : CMakeFiles/test_svr.dir/net/event_manage.cpp.o.requires

CMakeFiles/test_svr.dir/net/event_manage.cpp.o.provides: CMakeFiles/test_svr.dir/net/event_manage.cpp.o.requires
	$(MAKE) -f CMakeFiles/test_svr.dir/build.make CMakeFiles/test_svr.dir/net/event_manage.cpp.o.provides.build
.PHONY : CMakeFiles/test_svr.dir/net/event_manage.cpp.o.provides

CMakeFiles/test_svr.dir/net/event_manage.cpp.o.provides.build: CMakeFiles/test_svr.dir/net/event_manage.cpp.o

CMakeFiles/test_svr.dir/net/co_routine_mgr.cpp.o: CMakeFiles/test_svr.dir/flags.make
CMakeFiles/test_svr.dir/net/co_routine_mgr.cpp.o: ../net/co_routine_mgr.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/rylynnxj/Development/ryrpc/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/test_svr.dir/net/co_routine_mgr.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/test_svr.dir/net/co_routine_mgr.cpp.o -c /Users/rylynnxj/Development/ryrpc/net/co_routine_mgr.cpp

CMakeFiles/test_svr.dir/net/co_routine_mgr.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_svr.dir/net/co_routine_mgr.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/rylynnxj/Development/ryrpc/net/co_routine_mgr.cpp > CMakeFiles/test_svr.dir/net/co_routine_mgr.cpp.i

CMakeFiles/test_svr.dir/net/co_routine_mgr.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_svr.dir/net/co_routine_mgr.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/rylynnxj/Development/ryrpc/net/co_routine_mgr.cpp -o CMakeFiles/test_svr.dir/net/co_routine_mgr.cpp.s

CMakeFiles/test_svr.dir/net/co_routine_mgr.cpp.o.requires:
.PHONY : CMakeFiles/test_svr.dir/net/co_routine_mgr.cpp.o.requires

CMakeFiles/test_svr.dir/net/co_routine_mgr.cpp.o.provides: CMakeFiles/test_svr.dir/net/co_routine_mgr.cpp.o.requires
	$(MAKE) -f CMakeFiles/test_svr.dir/build.make CMakeFiles/test_svr.dir/net/co_routine_mgr.cpp.o.provides.build
.PHONY : CMakeFiles/test_svr.dir/net/co_routine_mgr.cpp.o.provides

CMakeFiles/test_svr.dir/net/co_routine_mgr.cpp.o.provides.build: CMakeFiles/test_svr.dir/net/co_routine_mgr.cpp.o

CMakeFiles/test_svr.dir/net/session.cpp.o: CMakeFiles/test_svr.dir/flags.make
CMakeFiles/test_svr.dir/net/session.cpp.o: ../net/session.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/rylynnxj/Development/ryrpc/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/test_svr.dir/net/session.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/test_svr.dir/net/session.cpp.o -c /Users/rylynnxj/Development/ryrpc/net/session.cpp

CMakeFiles/test_svr.dir/net/session.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_svr.dir/net/session.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/rylynnxj/Development/ryrpc/net/session.cpp > CMakeFiles/test_svr.dir/net/session.cpp.i

CMakeFiles/test_svr.dir/net/session.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_svr.dir/net/session.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/rylynnxj/Development/ryrpc/net/session.cpp -o CMakeFiles/test_svr.dir/net/session.cpp.s

CMakeFiles/test_svr.dir/net/session.cpp.o.requires:
.PHONY : CMakeFiles/test_svr.dir/net/session.cpp.o.requires

CMakeFiles/test_svr.dir/net/session.cpp.o.provides: CMakeFiles/test_svr.dir/net/session.cpp.o.requires
	$(MAKE) -f CMakeFiles/test_svr.dir/build.make CMakeFiles/test_svr.dir/net/session.cpp.o.provides.build
.PHONY : CMakeFiles/test_svr.dir/net/session.cpp.o.provides

CMakeFiles/test_svr.dir/net/session.cpp.o.provides.build: CMakeFiles/test_svr.dir/net/session.cpp.o

CMakeFiles/test_svr.dir/test.cc.o: CMakeFiles/test_svr.dir/flags.make
CMakeFiles/test_svr.dir/test.cc.o: ../test.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/rylynnxj/Development/ryrpc/build/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/test_svr.dir/test.cc.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/test_svr.dir/test.cc.o -c /Users/rylynnxj/Development/ryrpc/test.cc

CMakeFiles/test_svr.dir/test.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_svr.dir/test.cc.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/rylynnxj/Development/ryrpc/test.cc > CMakeFiles/test_svr.dir/test.cc.i

CMakeFiles/test_svr.dir/test.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_svr.dir/test.cc.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/rylynnxj/Development/ryrpc/test.cc -o CMakeFiles/test_svr.dir/test.cc.s

CMakeFiles/test_svr.dir/test.cc.o.requires:
.PHONY : CMakeFiles/test_svr.dir/test.cc.o.requires

CMakeFiles/test_svr.dir/test.cc.o.provides: CMakeFiles/test_svr.dir/test.cc.o.requires
	$(MAKE) -f CMakeFiles/test_svr.dir/build.make CMakeFiles/test_svr.dir/test.cc.o.provides.build
.PHONY : CMakeFiles/test_svr.dir/test.cc.o.provides

CMakeFiles/test_svr.dir/test.cc.o.provides.build: CMakeFiles/test_svr.dir/test.cc.o

# Object files for target test_svr
test_svr_OBJECTS = \
"CMakeFiles/test_svr.dir/main.cpp.o" \
"CMakeFiles/test_svr.dir/net/poller.cpp.o" \
"CMakeFiles/test_svr.dir/net/event_manage.cpp.o" \
"CMakeFiles/test_svr.dir/net/co_routine_mgr.cpp.o" \
"CMakeFiles/test_svr.dir/net/session.cpp.o" \
"CMakeFiles/test_svr.dir/test.cc.o"

# External object files for target test_svr
test_svr_EXTERNAL_OBJECTS = \
"/Users/rylynnxj/Development/ryrpc/common/switch_ctx.o"

test_svr: CMakeFiles/test_svr.dir/main.cpp.o
test_svr: CMakeFiles/test_svr.dir/net/poller.cpp.o
test_svr: CMakeFiles/test_svr.dir/net/event_manage.cpp.o
test_svr: CMakeFiles/test_svr.dir/net/co_routine_mgr.cpp.o
test_svr: CMakeFiles/test_svr.dir/net/session.cpp.o
test_svr: CMakeFiles/test_svr.dir/test.cc.o
test_svr: ../common/switch_ctx.o
test_svr: CMakeFiles/test_svr.dir/build.make
test_svr: CMakeFiles/test_svr.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable test_svr"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_svr.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_svr.dir/build: test_svr
.PHONY : CMakeFiles/test_svr.dir/build

CMakeFiles/test_svr.dir/requires: CMakeFiles/test_svr.dir/main.cpp.o.requires
CMakeFiles/test_svr.dir/requires: CMakeFiles/test_svr.dir/net/poller.cpp.o.requires
CMakeFiles/test_svr.dir/requires: CMakeFiles/test_svr.dir/net/event_manage.cpp.o.requires
CMakeFiles/test_svr.dir/requires: CMakeFiles/test_svr.dir/net/co_routine_mgr.cpp.o.requires
CMakeFiles/test_svr.dir/requires: CMakeFiles/test_svr.dir/net/session.cpp.o.requires
CMakeFiles/test_svr.dir/requires: CMakeFiles/test_svr.dir/test.cc.o.requires
.PHONY : CMakeFiles/test_svr.dir/requires

CMakeFiles/test_svr.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_svr.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_svr.dir/clean

CMakeFiles/test_svr.dir/depend:
	cd /Users/rylynnxj/Development/ryrpc/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/rylynnxj/Development/ryrpc /Users/rylynnxj/Development/ryrpc /Users/rylynnxj/Development/ryrpc/build /Users/rylynnxj/Development/ryrpc/build /Users/rylynnxj/Development/ryrpc/build/CMakeFiles/test_svr.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_svr.dir/depend

