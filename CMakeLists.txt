cmake_minimum_required(VERSION 3.5)

set(CMAKE_C_COMPILER /opt/homebrew/bin/gcc)
set(CMAKE_CXX_COMPILER /opt/homebrew/bin/g++)
project(cpp_playground)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(PROJECT_SOURCE_DIR ./src)



include_directories("/usr/include/opencv4/")
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR})
include_directories(/opt/homebrew/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/cereal/include)

add_definitions(-DPRJ_DIR="${CMAKE_CURRENT_SOURCE_DIR}/")

file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp ${PROJECT_SOURCE_DIR}/*.h)

add_executable(cpp_playground ../main.cpp)

target_include_directories(cpp_playground PUBLIC ${PROJECT_SOURCE_DIR}/src)
# target_link_libraries(cpp_playground )


