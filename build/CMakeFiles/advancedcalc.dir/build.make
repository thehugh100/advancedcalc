# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

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
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/hugh/Documents/tests/advancedcalc

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/hugh/Documents/tests/advancedcalc/build

# Include any dependencies generated for this target.
include CMakeFiles/advancedcalc.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/advancedcalc.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/advancedcalc.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/advancedcalc.dir/flags.make

CMakeFiles/advancedcalc.dir/main.cpp.o: CMakeFiles/advancedcalc.dir/flags.make
CMakeFiles/advancedcalc.dir/main.cpp.o: ../main.cpp
CMakeFiles/advancedcalc.dir/main.cpp.o: CMakeFiles/advancedcalc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/hugh/Documents/tests/advancedcalc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/advancedcalc.dir/main.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/advancedcalc.dir/main.cpp.o -MF CMakeFiles/advancedcalc.dir/main.cpp.o.d -o CMakeFiles/advancedcalc.dir/main.cpp.o -c /Users/hugh/Documents/tests/advancedcalc/main.cpp

CMakeFiles/advancedcalc.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/advancedcalc.dir/main.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/hugh/Documents/tests/advancedcalc/main.cpp > CMakeFiles/advancedcalc.dir/main.cpp.i

CMakeFiles/advancedcalc.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/advancedcalc.dir/main.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/hugh/Documents/tests/advancedcalc/main.cpp -o CMakeFiles/advancedcalc.dir/main.cpp.s

CMakeFiles/advancedcalc.dir/Calculator.cpp.o: CMakeFiles/advancedcalc.dir/flags.make
CMakeFiles/advancedcalc.dir/Calculator.cpp.o: ../Calculator.cpp
CMakeFiles/advancedcalc.dir/Calculator.cpp.o: CMakeFiles/advancedcalc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/hugh/Documents/tests/advancedcalc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/advancedcalc.dir/Calculator.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/advancedcalc.dir/Calculator.cpp.o -MF CMakeFiles/advancedcalc.dir/Calculator.cpp.o.d -o CMakeFiles/advancedcalc.dir/Calculator.cpp.o -c /Users/hugh/Documents/tests/advancedcalc/Calculator.cpp

CMakeFiles/advancedcalc.dir/Calculator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/advancedcalc.dir/Calculator.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/hugh/Documents/tests/advancedcalc/Calculator.cpp > CMakeFiles/advancedcalc.dir/Calculator.cpp.i

CMakeFiles/advancedcalc.dir/Calculator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/advancedcalc.dir/Calculator.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/hugh/Documents/tests/advancedcalc/Calculator.cpp -o CMakeFiles/advancedcalc.dir/Calculator.cpp.s

CMakeFiles/advancedcalc.dir/Token.cpp.o: CMakeFiles/advancedcalc.dir/flags.make
CMakeFiles/advancedcalc.dir/Token.cpp.o: ../Token.cpp
CMakeFiles/advancedcalc.dir/Token.cpp.o: CMakeFiles/advancedcalc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/hugh/Documents/tests/advancedcalc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/advancedcalc.dir/Token.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/advancedcalc.dir/Token.cpp.o -MF CMakeFiles/advancedcalc.dir/Token.cpp.o.d -o CMakeFiles/advancedcalc.dir/Token.cpp.o -c /Users/hugh/Documents/tests/advancedcalc/Token.cpp

CMakeFiles/advancedcalc.dir/Token.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/advancedcalc.dir/Token.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/hugh/Documents/tests/advancedcalc/Token.cpp > CMakeFiles/advancedcalc.dir/Token.cpp.i

CMakeFiles/advancedcalc.dir/Token.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/advancedcalc.dir/Token.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/hugh/Documents/tests/advancedcalc/Token.cpp -o CMakeFiles/advancedcalc.dir/Token.cpp.s

CMakeFiles/advancedcalc.dir/Parser.cpp.o: CMakeFiles/advancedcalc.dir/flags.make
CMakeFiles/advancedcalc.dir/Parser.cpp.o: ../Parser.cpp
CMakeFiles/advancedcalc.dir/Parser.cpp.o: CMakeFiles/advancedcalc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/hugh/Documents/tests/advancedcalc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/advancedcalc.dir/Parser.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/advancedcalc.dir/Parser.cpp.o -MF CMakeFiles/advancedcalc.dir/Parser.cpp.o.d -o CMakeFiles/advancedcalc.dir/Parser.cpp.o -c /Users/hugh/Documents/tests/advancedcalc/Parser.cpp

CMakeFiles/advancedcalc.dir/Parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/advancedcalc.dir/Parser.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/hugh/Documents/tests/advancedcalc/Parser.cpp > CMakeFiles/advancedcalc.dir/Parser.cpp.i

CMakeFiles/advancedcalc.dir/Parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/advancedcalc.dir/Parser.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/hugh/Documents/tests/advancedcalc/Parser.cpp -o CMakeFiles/advancedcalc.dir/Parser.cpp.s

CMakeFiles/advancedcalc.dir/Lexer.cpp.o: CMakeFiles/advancedcalc.dir/flags.make
CMakeFiles/advancedcalc.dir/Lexer.cpp.o: ../Lexer.cpp
CMakeFiles/advancedcalc.dir/Lexer.cpp.o: CMakeFiles/advancedcalc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/hugh/Documents/tests/advancedcalc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/advancedcalc.dir/Lexer.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/advancedcalc.dir/Lexer.cpp.o -MF CMakeFiles/advancedcalc.dir/Lexer.cpp.o.d -o CMakeFiles/advancedcalc.dir/Lexer.cpp.o -c /Users/hugh/Documents/tests/advancedcalc/Lexer.cpp

CMakeFiles/advancedcalc.dir/Lexer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/advancedcalc.dir/Lexer.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/hugh/Documents/tests/advancedcalc/Lexer.cpp > CMakeFiles/advancedcalc.dir/Lexer.cpp.i

CMakeFiles/advancedcalc.dir/Lexer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/advancedcalc.dir/Lexer.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/hugh/Documents/tests/advancedcalc/Lexer.cpp -o CMakeFiles/advancedcalc.dir/Lexer.cpp.s

CMakeFiles/advancedcalc.dir/TokenList.cpp.o: CMakeFiles/advancedcalc.dir/flags.make
CMakeFiles/advancedcalc.dir/TokenList.cpp.o: ../TokenList.cpp
CMakeFiles/advancedcalc.dir/TokenList.cpp.o: CMakeFiles/advancedcalc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/hugh/Documents/tests/advancedcalc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/advancedcalc.dir/TokenList.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/advancedcalc.dir/TokenList.cpp.o -MF CMakeFiles/advancedcalc.dir/TokenList.cpp.o.d -o CMakeFiles/advancedcalc.dir/TokenList.cpp.o -c /Users/hugh/Documents/tests/advancedcalc/TokenList.cpp

CMakeFiles/advancedcalc.dir/TokenList.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/advancedcalc.dir/TokenList.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/hugh/Documents/tests/advancedcalc/TokenList.cpp > CMakeFiles/advancedcalc.dir/TokenList.cpp.i

CMakeFiles/advancedcalc.dir/TokenList.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/advancedcalc.dir/TokenList.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/hugh/Documents/tests/advancedcalc/TokenList.cpp -o CMakeFiles/advancedcalc.dir/TokenList.cpp.s

CMakeFiles/advancedcalc.dir/Constants.cpp.o: CMakeFiles/advancedcalc.dir/flags.make
CMakeFiles/advancedcalc.dir/Constants.cpp.o: ../Constants.cpp
CMakeFiles/advancedcalc.dir/Constants.cpp.o: CMakeFiles/advancedcalc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/hugh/Documents/tests/advancedcalc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/advancedcalc.dir/Constants.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/advancedcalc.dir/Constants.cpp.o -MF CMakeFiles/advancedcalc.dir/Constants.cpp.o.d -o CMakeFiles/advancedcalc.dir/Constants.cpp.o -c /Users/hugh/Documents/tests/advancedcalc/Constants.cpp

CMakeFiles/advancedcalc.dir/Constants.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/advancedcalc.dir/Constants.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/hugh/Documents/tests/advancedcalc/Constants.cpp > CMakeFiles/advancedcalc.dir/Constants.cpp.i

CMakeFiles/advancedcalc.dir/Constants.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/advancedcalc.dir/Constants.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/hugh/Documents/tests/advancedcalc/Constants.cpp -o CMakeFiles/advancedcalc.dir/Constants.cpp.s

CMakeFiles/advancedcalc.dir/Helper.cpp.o: CMakeFiles/advancedcalc.dir/flags.make
CMakeFiles/advancedcalc.dir/Helper.cpp.o: ../Helper.cpp
CMakeFiles/advancedcalc.dir/Helper.cpp.o: CMakeFiles/advancedcalc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/hugh/Documents/tests/advancedcalc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/advancedcalc.dir/Helper.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/advancedcalc.dir/Helper.cpp.o -MF CMakeFiles/advancedcalc.dir/Helper.cpp.o.d -o CMakeFiles/advancedcalc.dir/Helper.cpp.o -c /Users/hugh/Documents/tests/advancedcalc/Helper.cpp

CMakeFiles/advancedcalc.dir/Helper.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/advancedcalc.dir/Helper.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/hugh/Documents/tests/advancedcalc/Helper.cpp > CMakeFiles/advancedcalc.dir/Helper.cpp.i

CMakeFiles/advancedcalc.dir/Helper.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/advancedcalc.dir/Helper.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/hugh/Documents/tests/advancedcalc/Helper.cpp -o CMakeFiles/advancedcalc.dir/Helper.cpp.s

CMakeFiles/advancedcalc.dir/Functions.cpp.o: CMakeFiles/advancedcalc.dir/flags.make
CMakeFiles/advancedcalc.dir/Functions.cpp.o: ../Functions.cpp
CMakeFiles/advancedcalc.dir/Functions.cpp.o: CMakeFiles/advancedcalc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/hugh/Documents/tests/advancedcalc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/advancedcalc.dir/Functions.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/advancedcalc.dir/Functions.cpp.o -MF CMakeFiles/advancedcalc.dir/Functions.cpp.o.d -o CMakeFiles/advancedcalc.dir/Functions.cpp.o -c /Users/hugh/Documents/tests/advancedcalc/Functions.cpp

CMakeFiles/advancedcalc.dir/Functions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/advancedcalc.dir/Functions.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/hugh/Documents/tests/advancedcalc/Functions.cpp > CMakeFiles/advancedcalc.dir/Functions.cpp.i

CMakeFiles/advancedcalc.dir/Functions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/advancedcalc.dir/Functions.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/hugh/Documents/tests/advancedcalc/Functions.cpp -o CMakeFiles/advancedcalc.dir/Functions.cpp.s

CMakeFiles/advancedcalc.dir/Font.cpp.o: CMakeFiles/advancedcalc.dir/flags.make
CMakeFiles/advancedcalc.dir/Font.cpp.o: ../Font.cpp
CMakeFiles/advancedcalc.dir/Font.cpp.o: CMakeFiles/advancedcalc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/hugh/Documents/tests/advancedcalc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/advancedcalc.dir/Font.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/advancedcalc.dir/Font.cpp.o -MF CMakeFiles/advancedcalc.dir/Font.cpp.o.d -o CMakeFiles/advancedcalc.dir/Font.cpp.o -c /Users/hugh/Documents/tests/advancedcalc/Font.cpp

CMakeFiles/advancedcalc.dir/Font.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/advancedcalc.dir/Font.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/hugh/Documents/tests/advancedcalc/Font.cpp > CMakeFiles/advancedcalc.dir/Font.cpp.i

CMakeFiles/advancedcalc.dir/Font.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/advancedcalc.dir/Font.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/hugh/Documents/tests/advancedcalc/Font.cpp -o CMakeFiles/advancedcalc.dir/Font.cpp.s

# Object files for target advancedcalc
advancedcalc_OBJECTS = \
"CMakeFiles/advancedcalc.dir/main.cpp.o" \
"CMakeFiles/advancedcalc.dir/Calculator.cpp.o" \
"CMakeFiles/advancedcalc.dir/Token.cpp.o" \
"CMakeFiles/advancedcalc.dir/Parser.cpp.o" \
"CMakeFiles/advancedcalc.dir/Lexer.cpp.o" \
"CMakeFiles/advancedcalc.dir/TokenList.cpp.o" \
"CMakeFiles/advancedcalc.dir/Constants.cpp.o" \
"CMakeFiles/advancedcalc.dir/Helper.cpp.o" \
"CMakeFiles/advancedcalc.dir/Functions.cpp.o" \
"CMakeFiles/advancedcalc.dir/Font.cpp.o"

# External object files for target advancedcalc
advancedcalc_EXTERNAL_OBJECTS =

advancedcalc: CMakeFiles/advancedcalc.dir/main.cpp.o
advancedcalc: CMakeFiles/advancedcalc.dir/Calculator.cpp.o
advancedcalc: CMakeFiles/advancedcalc.dir/Token.cpp.o
advancedcalc: CMakeFiles/advancedcalc.dir/Parser.cpp.o
advancedcalc: CMakeFiles/advancedcalc.dir/Lexer.cpp.o
advancedcalc: CMakeFiles/advancedcalc.dir/TokenList.cpp.o
advancedcalc: CMakeFiles/advancedcalc.dir/Constants.cpp.o
advancedcalc: CMakeFiles/advancedcalc.dir/Helper.cpp.o
advancedcalc: CMakeFiles/advancedcalc.dir/Functions.cpp.o
advancedcalc: CMakeFiles/advancedcalc.dir/Font.cpp.o
advancedcalc: CMakeFiles/advancedcalc.dir/build.make
advancedcalc: CMakeFiles/advancedcalc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/hugh/Documents/tests/advancedcalc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX executable advancedcalc"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/advancedcalc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/advancedcalc.dir/build: advancedcalc
.PHONY : CMakeFiles/advancedcalc.dir/build

CMakeFiles/advancedcalc.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/advancedcalc.dir/cmake_clean.cmake
.PHONY : CMakeFiles/advancedcalc.dir/clean

CMakeFiles/advancedcalc.dir/depend:
	cd /Users/hugh/Documents/tests/advancedcalc/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/hugh/Documents/tests/advancedcalc /Users/hugh/Documents/tests/advancedcalc /Users/hugh/Documents/tests/advancedcalc/build /Users/hugh/Documents/tests/advancedcalc/build /Users/hugh/Documents/tests/advancedcalc/build/CMakeFiles/advancedcalc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/advancedcalc.dir/depend

