cmake_minimum_required(VERSION 3.14)
if (POLICY CMP0122)
    cmake_policy(SET CMP0122 NEW)
endif()

project(gpiodcxx)

# set C++ standard
set(CMAKE_CXX_STANDARD 17)

# copy libc++_shared.so to the output directory
function(configure_shared_stl lib_path so_base)
    message("Configuring STL ${so_base} for ${ANDROID_ABI}")
    message("Copying ${ANDROID_NDK}/sources/cxx-stl/${lib_path}/libs/${ANDROID_ABI}/lib${so_base}.so to ${PROJECT_BINARY_DIR}/lib${so_base}.so")
    configure_file(
        "${ANDROID_NDK}/sources/cxx-stl/${lib_path}/libs/${ANDROID_ABI}/lib${so_base}.so" 
        "${CMAKE_CURRENT_BINARY_DIR}/lib${so_base}.so" 
        COPYONLY)
endfunction()
configure_shared_stl("llvm-libc++" "c++_shared")

# find SWIG
find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

# set output directories for generated files
set(CMAKE_SWIG_OUTDIR ${CMAKE_SOURCE_DIR}/bindings/csharp/)

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
    gpiodcxx
    # sets library as a shared library
    SHARED
    # path to the src
    ${SRC}
)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.
target_include_directories(gpiodcxx PUBLIC 
    ${PROJECT_SOURCE_DIR}/include/
    ${PROJECT_SOURCE_DIR}/tools/
    ${PROJECT_SOURCE_DIR}/bindings/cxx/
    ${PROJECT_SOURCE_DIR}/bindings/cxx/gpiodcxx
)

# add library dependencies
target_link_libraries(gpiodcxx gpiod)

# set_property(
#     TARGET gpiodcxx 
#     PROPERTY
#         SWIG_USE_TARGET_INCLUDE_DIRECTORIES TRUE
# )

# create a SWIG module
set_property(SOURCE gpiodcxx.i PROPERTY CPLUSPLUS ON)
set_property(SOURCE gpiodcxx.i PROPERTY SWIG_FLAGS "-namespace;gpiodroid;-dllimport;gpiodroid;-outfile;gpiodroid.cs;-cpperraswarn;")
set_property(SOURCE gpiodcxx.i PROPERTY SWIG_MODULE_NAME gpiodroid)
set_property(SOURCE gpiodcxx.i PROPERTY USE_SWIG_DEPENDENCIES TRUE)
set_property(SOURCE gpiodcxx.i PROPERTY SWIG_USE_TARGET_INCLUDE_DIRECTORIES TRUE)

swig_add_library(
    gpiodroid
    LANGUAGE csharp
    SOURCES gpiodcxx.i
)

swig_link_libraries(
    gpiodroid
    gpiodcxx
)

