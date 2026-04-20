cmake_minimum_required(VERSION 3.20)

# Cross-compile for 32-bit Windows with MinGW.
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
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_definitions(WIN32 _WINDOWS _USRDLL UNICODE _UNICODE)
add_compile_options(-ffunction-sections -fdata-sections -fpermissive)

# APCpp
# Build APCpp from its own CMakeLists and consume it as a static dependency.
set(APCPP_BUILD_SHARED OFF CACHE BOOL "Build APCpp as a static library" FORCE)
set(BUNDLED_JSONCPP ON CACHE BOOL "" FORCE)
if (MINGW)
    set(IXWEBSOCKET_SYSTEM_CERT_STORE OFF CACHE BOOL "Disable Windows certificate store" FORCE)
endif ()
add_subdirectory(lib/APCpp EXCLUDE_FROM_ALL)

# SADX Mod Loader
add_library(mod-loader-common STATIC
        lib/sadx-mod-loader-linux-compatible/ModLoaderCommon/IniFile.cpp
        lib/sadx-mod-loader-linux-compatible/ModLoaderCommon/TextConv.cpp)
target_include_directories(mod-loader-common SYSTEM PRIVATE
        ${CMAKE_SOURCE_DIR}/lib/sadx-mod-loader-linux-compatible/ModLoaderCommon
        ${CMAKE_SOURCE_DIR}/lib/sadx-mod-loader-linux-compatible)

# SADX Randomizer
file(GLOB_RECURSE RANDOMIZER_SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.cpp)
add_library(sadx-ap-randomizer SHARED ${RANDOMIZER_SOURCES})

target_include_directories(sadx-ap-randomizer PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_include_directories(sadx-ap-randomizer SYSTEM PRIVATE
        ${CMAKE_SOURCE_DIR}/lib/sadx-mod-loader-linux-compatible/ModLoaderCommon
        ${CMAKE_SOURCE_DIR}/lib/sadx-mod-loader-linux-compatible)

target_link_libraries(sadx-ap-randomizer PRIVATE mod-loader-common APCpp)

target_link_options(sadx-ap-randomizer PRIVATE -static-libgcc -static-libstdc++ -Wl,--gc-sections)

set_target_properties(sadx-ap-randomizer PROPERTIES PREFIX "" OUTPUT_NAME "sadx-classic-randomizer")

if(DEFINED SADX_MODS_DIR AND NOT SADX_MODS_DIR STREQUAL "")
    message(STATUS "Post-build copy enabled: ${SADX_MODS_DIR}")

    add_custom_command(TARGET sadx-ap-randomizer POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory "${SADX_MODS_DIR}"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:sadx-ap-randomizer>"
            "${SADX_MODS_DIR}/sadx-classic-randomizer.dll"
            VERBATIM
    )
else()
    message(STATUS "Post-build copy disabled (set -DSADX_MODS_DIR=... to enable).")
endif()
