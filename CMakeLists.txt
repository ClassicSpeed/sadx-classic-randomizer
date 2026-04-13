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


add_library(sadx-ap-randomizer SHARED
        src/mod2.cpp
        src/configuration/settings/Settings.cpp
        lib/sadx-mod-loader-linux-compatible/ModLoaderCommon/IniFile.cpp
        lib/sadx-mod-loader-linux-compatible/ModLoaderCommon/TextConv.cpp
)


target_compile_features(sadx-ap-randomizer PRIVATE cxx_std_17)

target_include_directories(sadx-ap-randomizer PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/lib/windows-header-fix
        ${CMAKE_SOURCE_DIR}/lib/json/include/json
        ${CMAKE_SOURCE_DIR}/lib/APCpp
        ${CMAKE_SOURCE_DIR}/lib/sadx-mod-loader-linux-compatible/ModLoaderCommon
        ${CMAKE_SOURCE_DIR}/lib/sadx-mod-loader-linux-compatible)

target_compile_definitions(sadx-ap-randomizer PRIVATE WIN32 _WINDOWS _USRDLL UNICODE _UNICODE)

target_link_options(sadx-ap-randomizer PRIVATE -static -static-libgcc -static-libstdc++)

set_target_properties(sadx-ap-randomizer PROPERTIES PREFIX "" OUTPUT_NAME "sadx-classic-randomizer")
