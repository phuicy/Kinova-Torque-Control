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
CMAKE_SOURCE_DIR = /home/phuicy/workspace/kinova-unilateral

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/phuicy/workspace/kinova-unilateral/build

# Include any dependencies generated for this target.
include test/CMakeFiles/KinovaTest.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/KinovaTest.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/KinovaTest.dir/flags.make

test/CMakeFiles/KinovaTest.dir/kinova_test.cpp.o: test/CMakeFiles/KinovaTest.dir/flags.make
test/CMakeFiles/KinovaTest.dir/kinova_test.cpp.o: ../test/kinova_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/phuicy/workspace/kinova-unilateral/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/KinovaTest.dir/kinova_test.cpp.o"
	cd /home/phuicy/workspace/kinova-unilateral/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/KinovaTest.dir/kinova_test.cpp.o -c /home/phuicy/workspace/kinova-unilateral/test/kinova_test.cpp

test/CMakeFiles/KinovaTest.dir/kinova_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/KinovaTest.dir/kinova_test.cpp.i"
	cd /home/phuicy/workspace/kinova-unilateral/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/phuicy/workspace/kinova-unilateral/test/kinova_test.cpp > CMakeFiles/KinovaTest.dir/kinova_test.cpp.i

test/CMakeFiles/KinovaTest.dir/kinova_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/KinovaTest.dir/kinova_test.cpp.s"
	cd /home/phuicy/workspace/kinova-unilateral/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/phuicy/workspace/kinova-unilateral/test/kinova_test.cpp -o CMakeFiles/KinovaTest.dir/kinova_test.cpp.s

# Object files for target KinovaTest
KinovaTest_OBJECTS = \
"CMakeFiles/KinovaTest.dir/kinova_test.cpp.o"

# External object files for target KinovaTest
KinovaTest_EXTERNAL_OBJECTS =

bin/KinovaTest: test/CMakeFiles/KinovaTest.dir/kinova_test.cpp.o
bin/KinovaTest: test/CMakeFiles/KinovaTest.dir/build.make
bin/KinovaTest: lib/libgtest_main.a
bin/KinovaTest: lib/libkinova.a
bin/KinovaTest: lib/libutils.a
bin/KinovaTest: lib/libgtest.a
bin/KinovaTest: /opt/ros/foxy/lib/librclcpp.so
bin/KinovaTest: /opt/ros/foxy/lib/liblibstatistics_collector.so
bin/KinovaTest: /opt/ros/foxy/lib/liblibstatistics_collector_test_msgs__rosidl_typesupport_introspection_c.so
bin/KinovaTest: /opt/ros/foxy/lib/liblibstatistics_collector_test_msgs__rosidl_generator_c.so
bin/KinovaTest: /opt/ros/foxy/lib/liblibstatistics_collector_test_msgs__rosidl_typesupport_c.so
bin/KinovaTest: /opt/ros/foxy/lib/liblibstatistics_collector_test_msgs__rosidl_typesupport_introspection_cpp.so
bin/KinovaTest: /opt/ros/foxy/lib/liblibstatistics_collector_test_msgs__rosidl_typesupport_cpp.so
bin/KinovaTest: /opt/ros/foxy/lib/librcl.so
bin/KinovaTest: /opt/ros/foxy/lib/librcl_interfaces__rosidl_typesupport_introspection_c.so
bin/KinovaTest: /opt/ros/foxy/lib/librcl_interfaces__rosidl_generator_c.so
bin/KinovaTest: /opt/ros/foxy/lib/librcl_interfaces__rosidl_typesupport_c.so
bin/KinovaTest: /opt/ros/foxy/lib/librcl_interfaces__rosidl_typesupport_introspection_cpp.so
bin/KinovaTest: /opt/ros/foxy/lib/librcl_interfaces__rosidl_typesupport_cpp.so
bin/KinovaTest: /opt/ros/foxy/lib/librmw_implementation.so
bin/KinovaTest: /opt/ros/foxy/lib/librmw.so
bin/KinovaTest: /opt/ros/foxy/lib/librcl_logging_spdlog.so
bin/KinovaTest: /usr/lib/x86_64-linux-gnu/libspdlog.so.1.5.0
bin/KinovaTest: /opt/ros/foxy/lib/librcl_yaml_param_parser.so
bin/KinovaTest: /opt/ros/foxy/lib/libyaml.so
bin/KinovaTest: /opt/ros/foxy/lib/librosgraph_msgs__rosidl_typesupport_introspection_c.so
bin/KinovaTest: /opt/ros/foxy/lib/librosgraph_msgs__rosidl_generator_c.so
bin/KinovaTest: /opt/ros/foxy/lib/librosgraph_msgs__rosidl_typesupport_c.so
bin/KinovaTest: /opt/ros/foxy/lib/librosgraph_msgs__rosidl_typesupport_introspection_cpp.so
bin/KinovaTest: /opt/ros/foxy/lib/librosgraph_msgs__rosidl_typesupport_cpp.so
bin/KinovaTest: /opt/ros/foxy/lib/libstatistics_msgs__rosidl_typesupport_introspection_c.so
bin/KinovaTest: /opt/ros/foxy/lib/libstatistics_msgs__rosidl_generator_c.so
bin/KinovaTest: /opt/ros/foxy/lib/libstatistics_msgs__rosidl_typesupport_c.so
bin/KinovaTest: /opt/ros/foxy/lib/libstatistics_msgs__rosidl_typesupport_introspection_cpp.so
bin/KinovaTest: /opt/ros/foxy/lib/libstatistics_msgs__rosidl_typesupport_cpp.so
bin/KinovaTest: /opt/ros/foxy/lib/libtracetools.so
bin/KinovaTest: /opt/ros/foxy/lib/libsensor_msgs__rosidl_typesupport_introspection_c.so
bin/KinovaTest: /opt/ros/foxy/lib/libsensor_msgs__rosidl_generator_c.so
bin/KinovaTest: /opt/ros/foxy/lib/libsensor_msgs__rosidl_typesupport_c.so
bin/KinovaTest: /opt/ros/foxy/lib/libsensor_msgs__rosidl_typesupport_introspection_cpp.so
bin/KinovaTest: /opt/ros/foxy/lib/libsensor_msgs__rosidl_typesupport_cpp.so
bin/KinovaTest: /opt/ros/foxy/lib/libgeometry_msgs__rosidl_typesupport_introspection_c.so
bin/KinovaTest: /opt/ros/foxy/lib/libgeometry_msgs__rosidl_generator_c.so
bin/KinovaTest: /opt/ros/foxy/lib/libgeometry_msgs__rosidl_typesupport_c.so
bin/KinovaTest: /opt/ros/foxy/lib/libgeometry_msgs__rosidl_typesupport_introspection_cpp.so
bin/KinovaTest: /opt/ros/foxy/lib/libgeometry_msgs__rosidl_typesupport_cpp.so
bin/KinovaTest: /opt/ros/foxy/lib/libstd_msgs__rosidl_typesupport_introspection_c.so
bin/KinovaTest: /opt/ros/foxy/lib/libstd_msgs__rosidl_generator_c.so
bin/KinovaTest: /opt/ros/foxy/lib/libstd_msgs__rosidl_typesupport_c.so
bin/KinovaTest: /opt/ros/foxy/lib/libstd_msgs__rosidl_typesupport_introspection_cpp.so
bin/KinovaTest: /opt/ros/foxy/lib/libstd_msgs__rosidl_typesupport_cpp.so
bin/KinovaTest: /opt/ros/foxy/lib/libbuiltin_interfaces__rosidl_typesupport_introspection_c.so
bin/KinovaTest: /opt/ros/foxy/lib/libbuiltin_interfaces__rosidl_generator_c.so
bin/KinovaTest: /opt/ros/foxy/lib/libbuiltin_interfaces__rosidl_typesupport_c.so
bin/KinovaTest: /opt/ros/foxy/lib/libbuiltin_interfaces__rosidl_typesupport_introspection_cpp.so
bin/KinovaTest: /opt/ros/foxy/lib/libbuiltin_interfaces__rosidl_typesupport_cpp.so
bin/KinovaTest: /opt/ros/foxy/lib/libstd_srvs__rosidl_typesupport_introspection_c.so
bin/KinovaTest: /opt/ros/foxy/lib/libstd_srvs__rosidl_generator_c.so
bin/KinovaTest: /opt/ros/foxy/lib/libstd_srvs__rosidl_typesupport_c.so
bin/KinovaTest: /opt/ros/foxy/lib/libstd_srvs__rosidl_typesupport_introspection_cpp.so
bin/KinovaTest: /opt/ros/foxy/lib/librosidl_typesupport_introspection_cpp.so
bin/KinovaTest: /opt/ros/foxy/lib/librosidl_typesupport_introspection_c.so
bin/KinovaTest: /opt/ros/foxy/lib/libstd_srvs__rosidl_typesupport_cpp.so
bin/KinovaTest: /opt/ros/foxy/lib/librosidl_typesupport_cpp.so
bin/KinovaTest: /opt/ros/foxy/lib/librosidl_typesupport_c.so
bin/KinovaTest: /opt/ros/foxy/lib/librcpputils.so
bin/KinovaTest: /opt/ros/foxy/lib/librosidl_runtime_c.so
bin/KinovaTest: /opt/ros/foxy/lib/librcutils.so
bin/KinovaTest: test/CMakeFiles/KinovaTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/phuicy/workspace/kinova-unilateral/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/KinovaTest"
	cd /home/phuicy/workspace/kinova-unilateral/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/KinovaTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/KinovaTest.dir/build: bin/KinovaTest

.PHONY : test/CMakeFiles/KinovaTest.dir/build

test/CMakeFiles/KinovaTest.dir/clean:
	cd /home/phuicy/workspace/kinova-unilateral/build/test && $(CMAKE_COMMAND) -P CMakeFiles/KinovaTest.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/KinovaTest.dir/clean

test/CMakeFiles/KinovaTest.dir/depend:
	cd /home/phuicy/workspace/kinova-unilateral/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/phuicy/workspace/kinova-unilateral /home/phuicy/workspace/kinova-unilateral/test /home/phuicy/workspace/kinova-unilateral/build /home/phuicy/workspace/kinova-unilateral/build/test /home/phuicy/workspace/kinova-unilateral/build/test/CMakeFiles/KinovaTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/KinovaTest.dir/depend
