cmake_minimum_required(VERSION 3.5)

project(kinova-bilateral VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR   ON)
set(CMAKE_VERBOSE_MAKEFILE      OFF)
set(CMAKE_COLOR_MAKEFILE        ON)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()


option(USE_CONAN "Use the Conan package manager to automatically fetch the Kortex API" ON)


# Activate C++ 11
set (CMAKE_CXX_STANDARD 17)


include(${PROJECT_SOURCE_DIR}/cmake/conan.cmake)

conan_check(REQUIRED)
conan_add_remote(
NAME kinova_public 
URL https://artifactory.kinovaapps.com/artifactory/api/conan/conan-public)


conan_cmake_run(REQUIRES kortex_api_cpp/2.3.0-r.34@kortex/stable
                SETTINGS kortex_api_cpp:compiler=gcc
                SETTINGS kortex_api_cpp:compiler.version=5
                SETTINGS compiler.libcxx=libstdc++11
                PROFILE_AUTO build_type
                BASIC_SETUP
                UPDATE)      


# Add Include Directories
include_directories(${KORTEX_DIR}include)
include_directories(${KORTEX_DIR}include/client)
include_directories(${KORTEX_DIR}include/common)
include_directories(${KORTEX_DIR}include/messages)
include_directories(${KORTEX_DIR}include/client_stubs)


add_definitions(-D_OS_UNIX)
add_compile_options(-Wall)
add_compile_options(-Wno-reorder)

include_directories(includes)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(eigen3_cmake_module)
find_package(std_srvs) 
find_package(Eigen3 REQUIRED)

include_directories(${EIGEN3_INCLUDE_DIR})

add_library(utils STATIC src/JointStatePublisher.cpp 
                         src/PD.cpp 
                         src/Math/Gravity.cpp 
                         src/Math/MassMatrix.cpp 
                         src/Math/Coriolis.cpp
                         src/Math/ForwardKinematics.cpp
                         src/KinovaControl.cpp
                         src/Math/InverseKinematics.cpp
                         src/Math/Jacobian.cpp
                         )
target_link_libraries(utils ${CONAN_LIBS} pthread ${EIGEN3_LIBS})
ament_target_dependencies(utils
  "rclcpp" "sensor_msgs" "std_msgs" "std_srvs")

add_library(kinova STATIC src/KinovaRobot.cpp src/KinovaControl.cpp src/LoopCycle.cpp src/DemandSubscriber.cpp)
target_link_libraries(kinova ${CONAN_LIBS} pthread ${EIGEN3_LIBS} utils) 
ament_target_dependencies(kinova
  "rclcpp" "sensor_msgs" "std_msgs" "std_srvs")

add_library(kinova_mock STATIC src/KinovaRobot_mock.cpp src/KinovaControl.cpp src/LoopCycle.cpp src/DemandSubscriber.cpp)
target_link_libraries(kinova_mock ${CONAN_LIBS} pthread ${EIGEN3_LIBS} utils) 
ament_target_dependencies(kinova_mock
  "rclcpp" "sensor_msgs" "std_msgs" "std_srvs")



add_executable(unilateral src/LoopCycle_unilateral.cpp unilateral.cpp)
target_link_libraries(unilateral ${CONAN_LIBS} pthread ${EIGEN3_LIBS} kinova utils) 
ament_target_dependencies(unilateral
  "rclcpp" "sensor_msgs" "std_msgs" "std_srvs")

add_executable(unilateral_mock src/LoopCycle_unilateral.cpp unilateral.cpp)
target_link_libraries(unilateral_mock ${CONAN_LIBS} pthread ${EIGEN3_LIBS} kinova_mock utils) 
ament_target_dependencies(unilateral_mock
  "rclcpp" "sensor_msgs" "std_msgs" "std_srvs")

  add_executable(taskspace src/LoopCycle_ik.cpp task-space-velocity.cpp src/TaskSubscriber.cpp)
  target_link_libraries(taskspace ${CONAN_LIBS} pthread ${EIGEN3_LIBS} kinova utils) 
  ament_target_dependencies(taskspace
    "rclcpp" "sensor_msgs" "std_msgs" "std_srvs" "geometry_msgs")
  
  add_executable(taskspace_mock src/LoopCycle_ik.cpp task-space-velocity.cpp src/TaskSubscriber.cpp)
  target_link_libraries(taskspace_mock ${CONAN_LIBS} pthread ${EIGEN3_LIBS} kinova_mock utils) 
  ament_target_dependencies(taskspace_mock
    "rclcpp" "sensor_msgs" "std_msgs" "std_srvs" "geometry_msgs")


# target_compile_options(unilateral PRIVATE -Wall -Wextra -Werror -fno-math-errno)

install(TARGETS unilateral unilateral_mock taskspace taskspace_mock)


  enable_testing()
  add_subdirectory (test)

  # first we can indicate the documentation build as an option and set it to ON by default
option(BUILD_DOC "Build documentation" ON)

# check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${PROJECT_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${PROJECT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)