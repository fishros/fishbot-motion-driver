# cmake needs this line
cmake_minimum_required(VERSION 3.0)
 
# Define project name
project(fishbot_motion_sdk)

include_directories(include)

SET(CMAKE_BUILD_TYPE DEBUG)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")
 
## System dependencies are found with CMake's conventions
find_package(Boost REQUIRED COMPONENTS
    thread
    # asio
)
 
if(NOT Boost_FOUND)
    message("NOT found Boost")
endif()
 
include_directories(${Boost_INCLUDE_DIRS})
# Declare the executable target built from your sources
add_executable(${PROJECT_NAME} 
    src/communicate/serial_communicate.cpp
    src/communicate/proto_utils.cpp
    src/test_main.cpp
)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})