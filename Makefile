# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/WaTheLs2FO/Documents/code/iAV

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/WaTheLs2FO/Documents/code/iAV

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake cache editor..."
	/usr/local/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake to regenerate build system..."
	/usr/local/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/WaTheLs2FO/Documents/code/iAV/CMakeFiles /Users/WaTheLs2FO/Documents/code/iAV//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/WaTheLs2FO/Documents/code/iAV/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named iAudioVisualizer

# Build rule for target.
iAudioVisualizer: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 iAudioVisualizer
.PHONY : iAudioVisualizer

# fast build rule for target.
iAudioVisualizer/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/iAudioVisualizer.dir/build.make CMakeFiles/iAudioVisualizer.dir/build
.PHONY : iAudioVisualizer/fast

main.o: main.cpp.o
.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/iAudioVisualizer.dir/build.make CMakeFiles/iAudioVisualizer.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i
.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/iAudioVisualizer.dir/build.make CMakeFiles/iAudioVisualizer.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s
.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/iAudioVisualizer.dir/build.make CMakeFiles/iAudioVisualizer.dir/main.cpp.s
.PHONY : main.cpp.s

src/ini.o: src/ini.c.o
.PHONY : src/ini.o

# target to build an object file
src/ini.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/iAudioVisualizer.dir/build.make CMakeFiles/iAudioVisualizer.dir/src/ini.c.o
.PHONY : src/ini.c.o

src/ini.i: src/ini.c.i
.PHONY : src/ini.i

# target to preprocess a source file
src/ini.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/iAudioVisualizer.dir/build.make CMakeFiles/iAudioVisualizer.dir/src/ini.c.i
.PHONY : src/ini.c.i

src/ini.s: src/ini.c.s
.PHONY : src/ini.s

# target to generate assembly for a file
src/ini.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/iAudioVisualizer.dir/build.make CMakeFiles/iAudioVisualizer.dir/src/ini.c.s
.PHONY : src/ini.c.s

src/kfc.o: src/kfc.c.o
.PHONY : src/kfc.o

# target to build an object file
src/kfc.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/iAudioVisualizer.dir/build.make CMakeFiles/iAudioVisualizer.dir/src/kfc.c.o
.PHONY : src/kfc.c.o

src/kfc.i: src/kfc.c.i
.PHONY : src/kfc.i

# target to preprocess a source file
src/kfc.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/iAudioVisualizer.dir/build.make CMakeFiles/iAudioVisualizer.dir/src/kfc.c.i
.PHONY : src/kfc.c.i

src/kfc.s: src/kfc.c.s
.PHONY : src/kfc.s

# target to generate assembly for a file
src/kfc.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/iAudioVisualizer.dir/build.make CMakeFiles/iAudioVisualizer.dir/src/kfc.c.s
.PHONY : src/kfc.c.s

src/kiss_fastfir.o: src/kiss_fastfir.c.o
.PHONY : src/kiss_fastfir.o

# target to build an object file
src/kiss_fastfir.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/iAudioVisualizer.dir/build.make CMakeFiles/iAudioVisualizer.dir/src/kiss_fastfir.c.o
.PHONY : src/kiss_fastfir.c.o

src/kiss_fastfir.i: src/kiss_fastfir.c.i
.PHONY : src/kiss_fastfir.i

# target to preprocess a source file
src/kiss_fastfir.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/iAudioVisualizer.dir/build.make CMakeFiles/iAudioVisualizer.dir/src/kiss_fastfir.c.i
.PHONY : src/kiss_fastfir.c.i

src/kiss_fastfir.s: src/kiss_fastfir.c.s
.PHONY : src/kiss_fastfir.s

# target to generate assembly for a file
src/kiss_fastfir.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/iAudioVisualizer.dir/build.make CMakeFiles/iAudioVisualizer.dir/src/kiss_fastfir.c.s
.PHONY : src/kiss_fastfir.c.s

src/kiss_fft.o: src/kiss_fft.c.o
.PHONY : src/kiss_fft.o

# target to build an object file
src/kiss_fft.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/iAudioVisualizer.dir/build.make CMakeFiles/iAudioVisualizer.dir/src/kiss_fft.c.o
.PHONY : src/kiss_fft.c.o

src/kiss_fft.i: src/kiss_fft.c.i
.PHONY : src/kiss_fft.i

# target to preprocess a source file
src/kiss_fft.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/iAudioVisualizer.dir/build.make CMakeFiles/iAudioVisualizer.dir/src/kiss_fft.c.i
.PHONY : src/kiss_fft.c.i

src/kiss_fft.s: src/kiss_fft.c.s
.PHONY : src/kiss_fft.s

# target to generate assembly for a file
src/kiss_fft.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/iAudioVisualizer.dir/build.make CMakeFiles/iAudioVisualizer.dir/src/kiss_fft.c.s
.PHONY : src/kiss_fft.c.s

src/kiss_fftnd.o: src/kiss_fftnd.c.o
.PHONY : src/kiss_fftnd.o

# target to build an object file
src/kiss_fftnd.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/iAudioVisualizer.dir/build.make CMakeFiles/iAudioVisualizer.dir/src/kiss_fftnd.c.o
.PHONY : src/kiss_fftnd.c.o

src/kiss_fftnd.i: src/kiss_fftnd.c.i
.PHONY : src/kiss_fftnd.i

# target to preprocess a source file
src/kiss_fftnd.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/iAudioVisualizer.dir/build.make CMakeFiles/iAudioVisualizer.dir/src/kiss_fftnd.c.i
.PHONY : src/kiss_fftnd.c.i

src/kiss_fftnd.s: src/kiss_fftnd.c.s
.PHONY : src/kiss_fftnd.s

# target to generate assembly for a file
src/kiss_fftnd.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/iAudioVisualizer.dir/build.make CMakeFiles/iAudioVisualizer.dir/src/kiss_fftnd.c.s
.PHONY : src/kiss_fftnd.c.s

src/kiss_fftndr.o: src/kiss_fftndr.c.o
.PHONY : src/kiss_fftndr.o

# target to build an object file
src/kiss_fftndr.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/iAudioVisualizer.dir/build.make CMakeFiles/iAudioVisualizer.dir/src/kiss_fftndr.c.o
.PHONY : src/kiss_fftndr.c.o

src/kiss_fftndr.i: src/kiss_fftndr.c.i
.PHONY : src/kiss_fftndr.i

# target to preprocess a source file
src/kiss_fftndr.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/iAudioVisualizer.dir/build.make CMakeFiles/iAudioVisualizer.dir/src/kiss_fftndr.c.i
.PHONY : src/kiss_fftndr.c.i

src/kiss_fftndr.s: src/kiss_fftndr.c.s
.PHONY : src/kiss_fftndr.s

# target to generate assembly for a file
src/kiss_fftndr.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/iAudioVisualizer.dir/build.make CMakeFiles/iAudioVisualizer.dir/src/kiss_fftndr.c.s
.PHONY : src/kiss_fftndr.c.s

src/kiss_fftr.o: src/kiss_fftr.c.o
.PHONY : src/kiss_fftr.o

# target to build an object file
src/kiss_fftr.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/iAudioVisualizer.dir/build.make CMakeFiles/iAudioVisualizer.dir/src/kiss_fftr.c.o
.PHONY : src/kiss_fftr.c.o

src/kiss_fftr.i: src/kiss_fftr.c.i
.PHONY : src/kiss_fftr.i

# target to preprocess a source file
src/kiss_fftr.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/iAudioVisualizer.dir/build.make CMakeFiles/iAudioVisualizer.dir/src/kiss_fftr.c.i
.PHONY : src/kiss_fftr.c.i

src/kiss_fftr.s: src/kiss_fftr.c.s
.PHONY : src/kiss_fftr.s

# target to generate assembly for a file
src/kiss_fftr.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/iAudioVisualizer.dir/build.make CMakeFiles/iAudioVisualizer.dir/src/kiss_fftr.c.s
.PHONY : src/kiss_fftr.c.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... iAudioVisualizer"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... src/ini.o"
	@echo "... src/ini.i"
	@echo "... src/ini.s"
	@echo "... src/kfc.o"
	@echo "... src/kfc.i"
	@echo "... src/kfc.s"
	@echo "... src/kiss_fastfir.o"
	@echo "... src/kiss_fastfir.i"
	@echo "... src/kiss_fastfir.s"
	@echo "... src/kiss_fft.o"
	@echo "... src/kiss_fft.i"
	@echo "... src/kiss_fft.s"
	@echo "... src/kiss_fftnd.o"
	@echo "... src/kiss_fftnd.i"
	@echo "... src/kiss_fftnd.s"
	@echo "... src/kiss_fftndr.o"
	@echo "... src/kiss_fftndr.i"
	@echo "... src/kiss_fftndr.s"
	@echo "... src/kiss_fftr.o"
	@echo "... src/kiss_fftr.i"
	@echo "... src/kiss_fftr.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

