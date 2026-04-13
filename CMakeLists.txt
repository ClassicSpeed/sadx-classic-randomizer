cmake_minimum_required(VERSION 3.20)

set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x86)

set(CMAKE_C_COMPILER i686-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER i686-w64-mingw32-g++)
set(CMAKE_RC_COMPILER i686-w64-mingw32-windres)

set(CMAKE_FIND_ROOT_PATH /usr/i686-w64-mingw32)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

project(sadx-ap-randomizer LANGUAGES CXX)

set(CONFIGURATION_DIR ${CMAKE_SOURCE_DIR}/src/configuration)
file(GLOB_RECURSE CONFIGURATION_SOURCES CONFIGURE_DEPENDS
        ${CONFIGURATION_DIR}/*.cpp
        ${CONFIGURATION_DIR}/*.h)

set(COMMON_INCLUDE_DIRS
        ${CMAKE_SOURCE_DIR}/src
        ${CONFIGURATION_DIR}
        ${CMAKE_SOURCE_DIR}/lib/windows-header-fix
        ${CMAKE_SOURCE_DIR}/lib/json/include/json
        ${CMAKE_SOURCE_DIR}/lib/APCpp
        ${CMAKE_SOURCE_DIR}/lib/sadx-mod-loader-linux-compatible/ModLoaderCommon
        ${CMAKE_SOURCE_DIR}/lib/sadx-mod-loader-linux-compatible)

set(COMMON_COMPILE_DEFINITIONS WIN32 _WINDOWS _USRDLL UNICODE _UNICODE)

# ModLoader Common
add_library(mod-loader-common STATIC
        lib/sadx-mod-loader-linux-compatible/ModLoaderCommon/IniFile.cpp
        lib/sadx-mod-loader-linux-compatible/ModLoaderCommon/TextConv.cpp)
target_compile_features(mod-loader-common PRIVATE cxx_std_17)
target_include_directories(mod-loader-common PRIVATE ${COMMON_INCLUDE_DIRS})
target_compile_definitions(mod-loader-common PRIVATE ${COMMON_COMPILE_DEFINITIONS})


# SADX AP Configurations
add_library(sadx-ap-randomizer-configuration OBJECT ${CONFIGURATION_SOURCES})
target_compile_features(sadx-ap-randomizer-configuration PRIVATE cxx_std_17)
target_include_directories(sadx-ap-randomizer-configuration PRIVATE ${COMMON_INCLUDE_DIRS})
target_compile_definitions(sadx-ap-randomizer-configuration PRIVATE ${COMMON_COMPILE_DEFINITIONS})


# SADX AP Randomizer Core
add_library(sadx-ap-randomizer-core OBJECT src/mod2.cpp)
add_dependencies(sadx-ap-randomizer-core sadx-ap-randomizer-configuration)
target_compile_features(sadx-ap-randomizer-core PRIVATE cxx_std_17)
target_include_directories(sadx-ap-randomizer-core PRIVATE ${COMMON_INCLUDE_DIRS})
target_compile_definitions(sadx-ap-randomizer-core PRIVATE ${COMMON_COMPILE_DEFINITIONS})

add_library(sadx-ap-randomizer SHARED
        $<TARGET_OBJECTS:sadx-ap-randomizer-configuration>
        $<TARGET_OBJECTS:sadx-ap-randomizer-core>)

target_link_libraries(sadx-ap-randomizer PRIVATE mod-loader-common)

target_link_options(sadx-ap-randomizer PRIVATE -static -static-libgcc -static-libstdc++)

set_target_properties(sadx-ap-randomizer PROPERTIES PREFIX "" OUTPUT_NAME "sadx-classic-randomizer")
