# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:
.PHONY : .NOTPARALLEL

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
CMAKE_SOURCE_DIR = /Users/wachs/Implementacao

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/wachs/Implementacao

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/opt/local/bin/ccmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/opt/local/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/wachs/Implementacao/CMakeFiles /Users/wachs/Implementacao/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/wachs/Implementacao/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named PhD

# Build rule for target.
PhD: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 PhD
.PHONY : PhD

# fast build rule for target.
PhD/fast:
	$(MAKE) -f CMakeFiles/PhD.dir/build.make CMakeFiles/PhD.dir/build
.PHONY : PhD/fast

Sources/Sources/AreaFeatureExtractor.o: Sources/Sources/AreaFeatureExtractor.cpp.o
.PHONY : Sources/Sources/AreaFeatureExtractor.o

# target to build an object file
Sources/Sources/AreaFeatureExtractor.cpp.o:
	$(MAKE) -f CMakeFiles/PhD.dir/build.make CMakeFiles/PhD.dir/Sources/Sources/AreaFeatureExtractor.cpp.o
.PHONY : Sources/Sources/AreaFeatureExtractor.cpp.o

Sources/Sources/AreaFeatureExtractor.i: Sources/Sources/AreaFeatureExtractor.cpp.i
.PHONY : Sources/Sources/AreaFeatureExtractor.i

# target to preprocess a source file
Sources/Sources/AreaFeatureExtractor.cpp.i:
	$(MAKE) -f CMakeFiles/PhD.dir/build.make CMakeFiles/PhD.dir/Sources/Sources/AreaFeatureExtractor.cpp.i
.PHONY : Sources/Sources/AreaFeatureExtractor.cpp.i

Sources/Sources/AreaFeatureExtractor.s: Sources/Sources/AreaFeatureExtractor.cpp.s
.PHONY : Sources/Sources/AreaFeatureExtractor.s

# target to generate assembly for a file
Sources/Sources/AreaFeatureExtractor.cpp.s:
	$(MAKE) -f CMakeFiles/PhD.dir/build.make CMakeFiles/PhD.dir/Sources/Sources/AreaFeatureExtractor.cpp.s
.PHONY : Sources/Sources/AreaFeatureExtractor.cpp.s

Sources/Sources/ComplexNetwork.o: Sources/Sources/ComplexNetwork.cpp.o
.PHONY : Sources/Sources/ComplexNetwork.o

# target to build an object file
Sources/Sources/ComplexNetwork.cpp.o:
	$(MAKE) -f CMakeFiles/PhD.dir/build.make CMakeFiles/PhD.dir/Sources/Sources/ComplexNetwork.cpp.o
.PHONY : Sources/Sources/ComplexNetwork.cpp.o

Sources/Sources/ComplexNetwork.i: Sources/Sources/ComplexNetwork.cpp.i
.PHONY : Sources/Sources/ComplexNetwork.i

# target to preprocess a source file
Sources/Sources/ComplexNetwork.cpp.i:
	$(MAKE) -f CMakeFiles/PhD.dir/build.make CMakeFiles/PhD.dir/Sources/Sources/ComplexNetwork.cpp.i
.PHONY : Sources/Sources/ComplexNetwork.cpp.i

Sources/Sources/ComplexNetwork.s: Sources/Sources/ComplexNetwork.cpp.s
.PHONY : Sources/Sources/ComplexNetwork.s

# target to generate assembly for a file
Sources/Sources/ComplexNetwork.cpp.s:
	$(MAKE) -f CMakeFiles/PhD.dir/build.make CMakeFiles/PhD.dir/Sources/Sources/ComplexNetwork.cpp.s
.PHONY : Sources/Sources/ComplexNetwork.cpp.s

Sources/Sources/ComplexNetworkConstructor.o: Sources/Sources/ComplexNetworkConstructor.cpp.o
.PHONY : Sources/Sources/ComplexNetworkConstructor.o

# target to build an object file
Sources/Sources/ComplexNetworkConstructor.cpp.o:
	$(MAKE) -f CMakeFiles/PhD.dir/build.make CMakeFiles/PhD.dir/Sources/Sources/ComplexNetworkConstructor.cpp.o
.PHONY : Sources/Sources/ComplexNetworkConstructor.cpp.o

Sources/Sources/ComplexNetworkConstructor.i: Sources/Sources/ComplexNetworkConstructor.cpp.i
.PHONY : Sources/Sources/ComplexNetworkConstructor.i

# target to preprocess a source file
Sources/Sources/ComplexNetworkConstructor.cpp.i:
	$(MAKE) -f CMakeFiles/PhD.dir/build.make CMakeFiles/PhD.dir/Sources/Sources/ComplexNetworkConstructor.cpp.i
.PHONY : Sources/Sources/ComplexNetworkConstructor.cpp.i

Sources/Sources/ComplexNetworkConstructor.s: Sources/Sources/ComplexNetworkConstructor.cpp.s
.PHONY : Sources/Sources/ComplexNetworkConstructor.s

# target to generate assembly for a file
Sources/Sources/ComplexNetworkConstructor.cpp.s:
	$(MAKE) -f CMakeFiles/PhD.dir/build.make CMakeFiles/PhD.dir/Sources/Sources/ComplexNetworkConstructor.cpp.s
.PHONY : Sources/Sources/ComplexNetworkConstructor.cpp.s

Sources/Sources/Edge.o: Sources/Sources/Edge.cpp.o
.PHONY : Sources/Sources/Edge.o

# target to build an object file
Sources/Sources/Edge.cpp.o:
	$(MAKE) -f CMakeFiles/PhD.dir/build.make CMakeFiles/PhD.dir/Sources/Sources/Edge.cpp.o
.PHONY : Sources/Sources/Edge.cpp.o

Sources/Sources/Edge.i: Sources/Sources/Edge.cpp.i
.PHONY : Sources/Sources/Edge.i

# target to preprocess a source file
Sources/Sources/Edge.cpp.i:
	$(MAKE) -f CMakeFiles/PhD.dir/build.make CMakeFiles/PhD.dir/Sources/Sources/Edge.cpp.i
.PHONY : Sources/Sources/Edge.cpp.i

Sources/Sources/Edge.s: Sources/Sources/Edge.cpp.s
.PHONY : Sources/Sources/Edge.s

# target to generate assembly for a file
Sources/Sources/Edge.cpp.s:
	$(MAKE) -f CMakeFiles/PhD.dir/build.make CMakeFiles/PhD.dir/Sources/Sources/Edge.cpp.s
.PHONY : Sources/Sources/Edge.cpp.s

Sources/Sources/Feature.o: Sources/Sources/Feature.cpp.o
.PHONY : Sources/Sources/Feature.o

# target to build an object file
Sources/Sources/Feature.cpp.o:
	$(MAKE) -f CMakeFiles/PhD.dir/build.make CMakeFiles/PhD.dir/Sources/Sources/Feature.cpp.o
.PHONY : Sources/Sources/Feature.cpp.o

Sources/Sources/Feature.i: Sources/Sources/Feature.cpp.i
.PHONY : Sources/Sources/Feature.i

# target to preprocess a source file
Sources/Sources/Feature.cpp.i:
	$(MAKE) -f CMakeFiles/PhD.dir/build.make CMakeFiles/PhD.dir/Sources/Sources/Feature.cpp.i
.PHONY : Sources/Sources/Feature.cpp.i

Sources/Sources/Feature.s: Sources/Sources/Feature.cpp.s
.PHONY : Sources/Sources/Feature.s

# target to generate assembly for a file
Sources/Sources/Feature.cpp.s:
	$(MAKE) -f CMakeFiles/PhD.dir/build.make CMakeFiles/PhD.dir/Sources/Sources/Feature.cpp.s
.PHONY : Sources/Sources/Feature.cpp.s

Sources/Sources/FeatureExtractor.o: Sources/Sources/FeatureExtractor.cpp.o
.PHONY : Sources/Sources/FeatureExtractor.o

# target to build an object file
Sources/Sources/FeatureExtractor.cpp.o:
	$(MAKE) -f CMakeFiles/PhD.dir/build.make CMakeFiles/PhD.dir/Sources/Sources/FeatureExtractor.cpp.o
.PHONY : Sources/Sources/FeatureExtractor.cpp.o

Sources/Sources/FeatureExtractor.i: Sources/Sources/FeatureExtractor.cpp.i
.PHONY : Sources/Sources/FeatureExtractor.i

# target to preprocess a source file
Sources/Sources/FeatureExtractor.cpp.i:
	$(MAKE) -f CMakeFiles/PhD.dir/build.make CMakeFiles/PhD.dir/Sources/Sources/FeatureExtractor.cpp.i
.PHONY : Sources/Sources/FeatureExtractor.cpp.i

Sources/Sources/FeatureExtractor.s: Sources/Sources/FeatureExtractor.cpp.s
.PHONY : Sources/Sources/FeatureExtractor.s

# target to generate assembly for a file
Sources/Sources/FeatureExtractor.cpp.s:
	$(MAKE) -f CMakeFiles/PhD.dir/build.make CMakeFiles/PhD.dir/Sources/Sources/FeatureExtractor.cpp.s
.PHONY : Sources/Sources/FeatureExtractor.cpp.s

Sources/Sources/HsvHistFeatureExtractor.o: Sources/Sources/HsvHistFeatureExtractor.cpp.o
.PHONY : Sources/Sources/HsvHistFeatureExtractor.o

# target to build an object file
Sources/Sources/HsvHistFeatureExtractor.cpp.o:
	$(MAKE) -f CMakeFiles/PhD.dir/build.make CMakeFiles/PhD.dir/Sources/Sources/HsvHistFeatureExtractor.cpp.o
.PHONY : Sources/Sources/HsvHistFeatureExtractor.cpp.o

Sources/Sources/HsvHistFeatureExtractor.i: Sources/Sources/HsvHistFeatureExtractor.cpp.i
.PHONY : Sources/Sources/HsvHistFeatureExtractor.i

# target to preprocess a source file
Sources/Sources/HsvHistFeatureExtractor.cpp.i:
	$(MAKE) -f CMakeFiles/PhD.dir/build.make CMakeFiles/PhD.dir/Sources/Sources/HsvHistFeatureExtractor.cpp.i
.PHONY : Sources/Sources/HsvHistFeatureExtractor.cpp.i

Sources/Sources/HsvHistFeatureExtractor.s: Sources/Sources/HsvHistFeatureExtractor.cpp.s
.PHONY : Sources/Sources/HsvHistFeatureExtractor.s

# target to generate assembly for a file
Sources/Sources/HsvHistFeatureExtractor.cpp.s:
	$(MAKE) -f CMakeFiles/PhD.dir/build.make CMakeFiles/PhD.dir/Sources/Sources/HsvHistFeatureExtractor.cpp.s
.PHONY : Sources/Sources/HsvHistFeatureExtractor.cpp.s

Sources/Sources/Link.o: Sources/Sources/Link.cpp.o
.PHONY : Sources/Sources/Link.o

# target to build an object file
Sources/Sources/Link.cpp.o:
	$(MAKE) -f CMakeFiles/PhD.dir/build.make CMakeFiles/PhD.dir/Sources/Sources/Link.cpp.o
.PHONY : Sources/Sources/Link.cpp.o

Sources/Sources/Link.i: Sources/Sources/Link.cpp.i
.PHONY : Sources/Sources/Link.i

# target to preprocess a source file
Sources/Sources/Link.cpp.i:
	$(MAKE) -f CMakeFiles/PhD.dir/build.make CMakeFiles/PhD.dir/Sources/Sources/Link.cpp.i
.PHONY : Sources/Sources/Link.cpp.i

Sources/Sources/Link.s: Sources/Sources/Link.cpp.s
.PHONY : Sources/Sources/Link.s

# target to generate assembly for a file
Sources/Sources/Link.cpp.s:
	$(MAKE) -f CMakeFiles/PhD.dir/build.make CMakeFiles/PhD.dir/Sources/Sources/Link.cpp.s
.PHONY : Sources/Sources/Link.cpp.s

Sources/Sources/Node.o: Sources/Sources/Node.cpp.o
.PHONY : Sources/Sources/Node.o

# target to build an object file
Sources/Sources/Node.cpp.o:
	$(MAKE) -f CMakeFiles/PhD.dir/build.make CMakeFiles/PhD.dir/Sources/Sources/Node.cpp.o
.PHONY : Sources/Sources/Node.cpp.o

Sources/Sources/Node.i: Sources/Sources/Node.cpp.i
.PHONY : Sources/Sources/Node.i

# target to preprocess a source file
Sources/Sources/Node.cpp.i:
	$(MAKE) -f CMakeFiles/PhD.dir/build.make CMakeFiles/PhD.dir/Sources/Sources/Node.cpp.i
.PHONY : Sources/Sources/Node.cpp.i

Sources/Sources/Node.s: Sources/Sources/Node.cpp.s
.PHONY : Sources/Sources/Node.s

# target to generate assembly for a file
Sources/Sources/Node.cpp.s:
	$(MAKE) -f CMakeFiles/PhD.dir/build.make CMakeFiles/PhD.dir/Sources/Sources/Node.cpp.s
.PHONY : Sources/Sources/Node.cpp.s

Sources/Sources/Region.o: Sources/Sources/Region.cpp.o
.PHONY : Sources/Sources/Region.o

# target to build an object file
Sources/Sources/Region.cpp.o:
	$(MAKE) -f CMakeFiles/PhD.dir/build.make CMakeFiles/PhD.dir/Sources/Sources/Region.cpp.o
.PHONY : Sources/Sources/Region.cpp.o

Sources/Sources/Region.i: Sources/Sources/Region.cpp.i
.PHONY : Sources/Sources/Region.i

# target to preprocess a source file
Sources/Sources/Region.cpp.i:
	$(MAKE) -f CMakeFiles/PhD.dir/build.make CMakeFiles/PhD.dir/Sources/Sources/Region.cpp.i
.PHONY : Sources/Sources/Region.cpp.i

Sources/Sources/Region.s: Sources/Sources/Region.cpp.s
.PHONY : Sources/Sources/Region.s

# target to generate assembly for a file
Sources/Sources/Region.cpp.s:
	$(MAKE) -f CMakeFiles/PhD.dir/build.make CMakeFiles/PhD.dir/Sources/Sources/Region.cpp.s
.PHONY : Sources/Sources/Region.cpp.s

Sources/Sources/SunDatabaseReader.o: Sources/Sources/SunDatabaseReader.cpp.o
.PHONY : Sources/Sources/SunDatabaseReader.o

# target to build an object file
Sources/Sources/SunDatabaseReader.cpp.o:
	$(MAKE) -f CMakeFiles/PhD.dir/build.make CMakeFiles/PhD.dir/Sources/Sources/SunDatabaseReader.cpp.o
.PHONY : Sources/Sources/SunDatabaseReader.cpp.o

Sources/Sources/SunDatabaseReader.i: Sources/Sources/SunDatabaseReader.cpp.i
.PHONY : Sources/Sources/SunDatabaseReader.i

# target to preprocess a source file
Sources/Sources/SunDatabaseReader.cpp.i:
	$(MAKE) -f CMakeFiles/PhD.dir/build.make CMakeFiles/PhD.dir/Sources/Sources/SunDatabaseReader.cpp.i
.PHONY : Sources/Sources/SunDatabaseReader.cpp.i

Sources/Sources/SunDatabaseReader.s: Sources/Sources/SunDatabaseReader.cpp.s
.PHONY : Sources/Sources/SunDatabaseReader.s

# target to generate assembly for a file
Sources/Sources/SunDatabaseReader.cpp.s:
	$(MAKE) -f CMakeFiles/PhD.dir/build.make CMakeFiles/PhD.dir/Sources/Sources/SunDatabaseReader.cpp.s
.PHONY : Sources/Sources/SunDatabaseReader.cpp.s

Sources/Sources/SupervisedImage.o: Sources/Sources/SupervisedImage.cpp.o
.PHONY : Sources/Sources/SupervisedImage.o

# target to build an object file
Sources/Sources/SupervisedImage.cpp.o:
	$(MAKE) -f CMakeFiles/PhD.dir/build.make CMakeFiles/PhD.dir/Sources/Sources/SupervisedImage.cpp.o
.PHONY : Sources/Sources/SupervisedImage.cpp.o

Sources/Sources/SupervisedImage.i: Sources/Sources/SupervisedImage.cpp.i
.PHONY : Sources/Sources/SupervisedImage.i

# target to preprocess a source file
Sources/Sources/SupervisedImage.cpp.i:
	$(MAKE) -f CMakeFiles/PhD.dir/build.make CMakeFiles/PhD.dir/Sources/Sources/SupervisedImage.cpp.i
.PHONY : Sources/Sources/SupervisedImage.cpp.i

Sources/Sources/SupervisedImage.s: Sources/Sources/SupervisedImage.cpp.s
.PHONY : Sources/Sources/SupervisedImage.s

# target to generate assembly for a file
Sources/Sources/SupervisedImage.cpp.s:
	$(MAKE) -f CMakeFiles/PhD.dir/build.make CMakeFiles/PhD.dir/Sources/Sources/SupervisedImage.cpp.s
.PHONY : Sources/Sources/SupervisedImage.cpp.s

Sources/Sources/main.o: Sources/Sources/main.cpp.o
.PHONY : Sources/Sources/main.o

# target to build an object file
Sources/Sources/main.cpp.o:
	$(MAKE) -f CMakeFiles/PhD.dir/build.make CMakeFiles/PhD.dir/Sources/Sources/main.cpp.o
.PHONY : Sources/Sources/main.cpp.o

Sources/Sources/main.i: Sources/Sources/main.cpp.i
.PHONY : Sources/Sources/main.i

# target to preprocess a source file
Sources/Sources/main.cpp.i:
	$(MAKE) -f CMakeFiles/PhD.dir/build.make CMakeFiles/PhD.dir/Sources/Sources/main.cpp.i
.PHONY : Sources/Sources/main.cpp.i

Sources/Sources/main.s: Sources/Sources/main.cpp.s
.PHONY : Sources/Sources/main.s

# target to generate assembly for a file
Sources/Sources/main.cpp.s:
	$(MAKE) -f CMakeFiles/PhD.dir/build.make CMakeFiles/PhD.dir/Sources/Sources/main.cpp.s
.PHONY : Sources/Sources/main.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... PhD"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... Sources/Sources/AreaFeatureExtractor.o"
	@echo "... Sources/Sources/AreaFeatureExtractor.i"
	@echo "... Sources/Sources/AreaFeatureExtractor.s"
	@echo "... Sources/Sources/ComplexNetwork.o"
	@echo "... Sources/Sources/ComplexNetwork.i"
	@echo "... Sources/Sources/ComplexNetwork.s"
	@echo "... Sources/Sources/ComplexNetworkConstructor.o"
	@echo "... Sources/Sources/ComplexNetworkConstructor.i"
	@echo "... Sources/Sources/ComplexNetworkConstructor.s"
	@echo "... Sources/Sources/Edge.o"
	@echo "... Sources/Sources/Edge.i"
	@echo "... Sources/Sources/Edge.s"
	@echo "... Sources/Sources/Feature.o"
	@echo "... Sources/Sources/Feature.i"
	@echo "... Sources/Sources/Feature.s"
	@echo "... Sources/Sources/FeatureExtractor.o"
	@echo "... Sources/Sources/FeatureExtractor.i"
	@echo "... Sources/Sources/FeatureExtractor.s"
	@echo "... Sources/Sources/HsvHistFeatureExtractor.o"
	@echo "... Sources/Sources/HsvHistFeatureExtractor.i"
	@echo "... Sources/Sources/HsvHistFeatureExtractor.s"
	@echo "... Sources/Sources/Link.o"
	@echo "... Sources/Sources/Link.i"
	@echo "... Sources/Sources/Link.s"
	@echo "... Sources/Sources/Node.o"
	@echo "... Sources/Sources/Node.i"
	@echo "... Sources/Sources/Node.s"
	@echo "... Sources/Sources/Region.o"
	@echo "... Sources/Sources/Region.i"
	@echo "... Sources/Sources/Region.s"
	@echo "... Sources/Sources/SunDatabaseReader.o"
	@echo "... Sources/Sources/SunDatabaseReader.i"
	@echo "... Sources/Sources/SunDatabaseReader.s"
	@echo "... Sources/Sources/SupervisedImage.o"
	@echo "... Sources/Sources/SupervisedImage.i"
	@echo "... Sources/Sources/SupervisedImage.s"
	@echo "... Sources/Sources/main.o"
	@echo "... Sources/Sources/main.i"
	@echo "... Sources/Sources/main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

