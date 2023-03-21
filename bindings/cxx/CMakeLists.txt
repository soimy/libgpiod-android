cmake_minimum_required(VERSION 3.14)
if (POLICY CMP0122)
    cmake_policy(SET CMP0122 NEW)
endif()

project(gpiodroid)

# set C++ standard
set(CMAKE_CXX_STANDARD 17)

# find SWIG
find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

# set output directories for generated files
set(CMAKE_SWIG_OUTDIR ${CMAKE_SOURCE_DIR}/bindings/csharp/swig_cxx)
# set(SWIG_OUTFILE_NAME gpiodroid.cs)

# add include directories
include_directories(
    ${ANDROID_ABI}/
    ${CMAKE_SOURCE_DIR}/include/
    ${CMAKE_SOURCE_DIR}/tools/
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/gpiodcxx
)

aux_source_directory(${CMAKE_SOURCE_DIR}/bindings/cxx SRC)

# add library source files
add_library(
    # name of the library
    gpiodroid
    # sets library as a shared library
    SHARED
    # path to the src
    ${SRC}
)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.
target_include_directories(gpiodroid PUBLIC 
    ${PROJECT_SOURCE_DIR}/include/
    ${PROJECT_SOURCE_DIR}/tools/
    ${PROJECT_SOURCE_DIR}/bindings/cxx/
    ${PROJECT_SOURCE_DIR}/bindings/cxx/gpiodcxx
)

# add library dependencies
target_link_libraries(gpiodroid gpiod)

set_property(
    TARGET gpiodroid 
    PROPERTY
        SWIG_USE_TARGET_INCLUDE_DIRECTORIES TRUE
)

# create a SWIG module
set_source_files_properties(gpiodroid.i PROPERTIES CPLUSPLUS ON)
set_source_files_properties(gpiodroid.i PROPERTIES SWIG_FLAGS "-namespace;gpiodroid")
# set_source_files_properties(gpiodroid.i PROPERTIES SWIG_FLAGS "-includeall")
# set_source_files_properties(gpiodroid.i PROPERTIES SWIG_FLAGS "-outfile gpiodroid_csharp.cs")
swig_add_library(
    gpiodroid_csharp
    LANGUAGE csharp
    SOURCES gpiodroid.i
)

swig_link_libraries(
    gpiodroid_csharp
    gpiodroid
)

