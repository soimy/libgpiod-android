# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.22.1)

# Declares and names the project.

project("gpiod" VERSION 2.0)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
aux_source_directory(lib/ GPIOD_C_SRC)
aux_source_directory(include/ GPIOD_C_INC)
# aux_source_directory(bindings/csharp/ GPIOD_CS_SRC)
# aux_source_directory(tools/ GPIOD_C_TOOLS)
# aux_source_directory(bindings/cxx/ GPIOD_CPP_SRC)
file(GLOB TOOL_COMMON_SRC
        "${PROJECT_SOURCE_DIR}/tools/tools-common.c"
        "${PROJECT_SOURCE_DIR}/tools/tools-common.h"
        "${PROJECT_SOURCE_DIR}/bindings/csharp/gpiodWrapper.c"
        "${PROJECT_SOURCE_DIR}/bindings/csharp/gpiodWrapper.h"
        )

add_library( # Sets the name of the library.
        gpiod

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        ${GPIOD_C_SRC}
        ${GPIOD_C_INC}
        ${TOOL_COMMON_SRC}
        # ${GPIOD_CS_SRC}
        # ${GPIOD_C_TOOLS}
        # ${GPIOD_CPP_SRC}
        )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before  
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)
# find_library(cxx-lib libc++)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -stdlib=libc++")
# set(CMAKE_EXE_LINKER_FLAGS "-lc++abi")

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

include_directories(
        ${ANDROID_ABI}/
        ${PROJECT_SOURCE_DIR}/include/
        ${PROJECT_SOURCE_DIR}/tools/
        )

target_include_directories(gpiod PRIVATE 
        ${PROJECT_SOURCE_DIR}/include/
        ${PROJECT_SOURCE_DIR}/tools/
        )
target_link_libraries( # Specifies the target library.
        gpiod

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib}
        # ${cxx-lib}
)

add_subdirectory(
        ${PROJECT_SOURCE_DIR}/bindings/csharp/
)