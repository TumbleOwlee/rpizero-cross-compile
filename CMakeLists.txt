# Set version requirement
cmake_minimum_required(VERSION 3.16)

# Export compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set default to Debug
if("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    set(CMAKE_BUILD_TYPE "RelWithDebInfo")
endif()
message("Build type: ${CMAKE_BUILD_TYPE}")

set(BUILD_SHARED_LIBS OFF)

if(RASPBERRY)
    set(CMAKE_SYSROOT "${CMAKE_CURRENT_SOURCE_DIR}/env/chroot/armv6")
    set(CMAKE_FIND_ROOT_PATH "${CMAKE_SYSROOT}")
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/env/compiler/armv6/x-tools/armv6-rpi-linux-gnueabihf/armv6-rpi-linux-gnueabihf.toolchain.cmake")
endif()

# Define project
project(sentry-example
    VERSION 0.0.1
    DESCRIPTION "Simple example application of sentry."
    LANGUAGES C CXX)

# Create list of all test files
set(SOURCE_FILES
    "src/main.cxx"
)

add_subdirectory("deps/sentry")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/deps/sentry/include)
target_link_libraries(${PROJECT_NAME} PRIVATE sentry)
