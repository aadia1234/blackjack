cmake_minimum_required(VERSION 3.10)
project(BlackjackNative)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -arch arm64")
set(CMAKE_OSX_ARCHITECTURES "arm64")

# Find JNI
find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})
include_directories(include)

# Add source files
file(GLOB SOURCES "src/*.cpp")

# Create shared library
add_library(BlackjackNative SHARED ${SOURCES})
target_link_libraries(BlackjackNative ${JNI_LIBRARIES})

# Make sure Card.h and other headers are correctly included
target_include_directories(BlackjackNative PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)