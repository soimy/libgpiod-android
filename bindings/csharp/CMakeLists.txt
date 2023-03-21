cmake_minimum_required(VERSION 3.14)
if (POLICY CMP0122)
    cmake_policy(SET CMP0122 NEW)
endif()

project(gpiodroid)

# set C++ standard
# set(CMAKE_CXX_STANDARD 17)

# find SWIG
find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

# set output directories for generated files
set(CMAKE_SWIG_OUTDIR ${CMAKE_SOURCE_DIR}/bindings/csharp/swig)
set(SWIG_OUTFILE_NAME gpiodroid.cs)

# add include directories
include_directories(
    ${ANDROID_ABI}/
    ${CMAKE_SOURCE_DIR}/include/
    ${CMAKE_SOURCE_DIR}/lib/
    ${CMAKE_SOURCE_DIR}/tools/
)

aux_source_directory(${CMAKE_SOURCE_DIR}/lib SRC)
file(GLOB TOOL_COMMON_SRC
    "${PROJECT_SOURCE_DIR}/tools/tools-common.c"
    "${PROJECT_SOURCE_DIR}/tools/tools-common.h"
)


# add library source files
add_library(
    # name of the library
    gpiodroid
    # sets library as a shared library
    SHARED
    # path to the src
    ${SRC}
    ${TOOL_COMMON_SRC}
)

# add library dependencies
target_link_libraries(gpiodroid gpiod)

# create a SWIG module
# set_source_files_properties(gpiod.i PROPERTIES CPLUSPLUS ON)
set_source_files_properties(gpiod.i PROPERTIES SWIG_FLAGS "-namespace;gpiodroid")
# set_source_files_properties(gpiod.i PROPERTIES SWIG_FLAGS "-includeall")
# set_source_files_properties(gpiodroid.i PROPERTIES SWIG_FLAGS "-outfile gpiodroid_csharp.cs")
swig_add_library(
    gpiodroid_csharp
    LANGUAGE csharp
    SOURCES gpiod.i
)

set_property(
    TARGET gpiodroid_csharp
    PROPERTY
        SWIG_USE_TARGET_INCLUDE_DIRECTORIES TRUE
)
swig_link_libraries(
    gpiodroid_csharp
    gpiodroid
)

