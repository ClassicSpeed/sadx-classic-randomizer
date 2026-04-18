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

# Pull APCpp dependency targets (ixwebsocket/jsoncpp/mbedtls/zlib),
# but compile Archipelago sources directly into this project's DLL.
set(BUNDLED_JSONCPP ON CACHE BOOL "" FORCE)

if(MINGW)
    set(IXWEBSOCKET_SYSTEM_CERT_STORE OFF CACHE BOOL "Disable Windows certificate store" FORCE)
endif()

add_subdirectory(lib/APCpp EXCLUDE_FROM_ALL)

if(MINGW AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND TARGET ixwebsocket)
    find_library(MINGW_CRYPT32_LIBRARY NAMES crypt32)
    if(NOT MINGW_CRYPT32_LIBRARY)
        set(MINGW_CRYPT32_LIBRARY /usr/i686-w64-mingw32/lib/libcrypt32.a)
    endif()

    function(replace_target_link_item target old_item new_item)
        foreach(link_property LINK_LIBRARIES INTERFACE_LINK_LIBRARIES)
            get_target_property(link_items ${target} ${link_property})
            if(link_items AND NOT link_items STREQUAL "link_items-NOTFOUND")
                set(updated_link_items "")
                set(link_items_changed FALSE)
                foreach(link_item IN LISTS link_items)
                    if(link_item STREQUAL "${old_item}")
                        list(APPEND updated_link_items "${new_item}")
                        set(link_items_changed TRUE)
                    elseif(link_item STREQUAL "$<LINK_ONLY:${old_item}>")
                        list(APPEND updated_link_items "$<LINK_ONLY:${new_item}>")
                        set(link_items_changed TRUE)
                    else()
                        list(APPEND updated_link_items "${link_item}")
                    endif()
                endforeach()
                if(link_items_changed)
                    set_target_properties(${target} PROPERTIES ${link_property} "${updated_link_items}")
                endif()
            endif()
        endforeach()
    endfunction()

    if(EXISTS "${MINGW_CRYPT32_LIBRARY}")
        replace_target_link_item(ixwebsocket Crypt32 "${MINGW_CRYPT32_LIBRARY}")
    endif()
endif()

set(CONFIGURATION_DIR ${CMAKE_SOURCE_DIR}/src/configuration)
file(GLOB_RECURSE CONFIGURATION_SOURCES CONFIGURE_DEPENDS
        ${CONFIGURATION_DIR}/*.cpp
        ${CONFIGURATION_DIR}/*.h)

set(COMMON_INCLUDE_DIRS
        ${CMAKE_SOURCE_DIR}/src
        ${CONFIGURATION_DIR}
        ${CMAKE_SOURCE_DIR}/lib/APCpp
        ${CMAKE_SOURCE_DIR}/lib/APCpp/IXWebSocket
        ${CMAKE_SOURCE_DIR}/lib/APCpp/jsoncpp/include
        ${CMAKE_SOURCE_DIR}/lib/windows-header-fix)

set(MOD_LOADER_INCLUDE_DIRS
        ${CMAKE_SOURCE_DIR}/lib/sadx-mod-loader-linux-compatible/ModLoaderCommon
        ${CMAKE_SOURCE_DIR}/lib/sadx-mod-loader-linux-compatible)

set(COMMON_COMPILE_DEFINITIONS WIN32 _WINDOWS _USRDLL UNICODE _UNICODE)
set(COMMON_SECTION_COMPILE_OPTIONS -ffunction-sections -fdata-sections)

function(apply_common_target_settings target)
    target_compile_features(${target} PRIVATE cxx_std_17)
    target_include_directories(${target} PRIVATE ${COMMON_INCLUDE_DIRS})
    target_include_directories(${target} SYSTEM PRIVATE ${MOD_LOADER_INCLUDE_DIRS})
    target_compile_definitions(${target} PRIVATE ${COMMON_COMPILE_DEFINITIONS})
endfunction()

# ModLoader Common
add_library(mod-loader-common STATIC
        lib/sadx-mod-loader-linux-compatible/ModLoaderCommon/IniFile.cpp
        lib/sadx-mod-loader-linux-compatible/ModLoaderCommon/TextConv.cpp)
apply_common_target_settings(mod-loader-common)


# SADX AP Configurations
add_library(sadx-ap-randomizer-configuration OBJECT ${CONFIGURATION_SOURCES})
apply_common_target_settings(sadx-ap-randomizer-configuration)

target_compile_options(sadx-ap-randomizer-configuration PRIVATE
        ${COMMON_SECTION_COMPILE_OPTIONS})

file(GLOB_RECURSE RANDOMIZER_SOURCES CONFIGURE_DEPENDS
        ${CMAKE_SOURCE_DIR}/src/*.cpp)

# src/configuration is compiled via sadx-ap-randomizer-configuration.
list(FILTER RANDOMIZER_SOURCES EXCLUDE REGEX "^${CONFIGURATION_DIR}/")

set(APCPP_SOURCES
        lib/APCpp/Archipelago.cpp
        lib/APCpp/Archipelago_DataStorageSim.cpp
        lib/APCpp/Archipelago_Gifting.cpp)

add_library(sadx-ap-randomizer SHARED
        $<TARGET_OBJECTS:sadx-ap-randomizer-configuration>)

target_sources(sadx-ap-randomizer PRIVATE
        ${APCPP_SOURCES}
        ${RANDOMIZER_SOURCES})

apply_common_target_settings(sadx-ap-randomizer)

target_compile_options(sadx-ap-randomizer PRIVATE
        -fpermissive
        ${COMMON_SECTION_COMPILE_OPTIONS})


target_link_libraries(sadx-ap-randomizer PRIVATE
        mod-loader-common
        ixwebsocket
        jsoncpp_static
        mbedtls
        mbedx509
        mbedcrypto
        zlibstatic
        wsock32
        ws2_32
        shlwapi
        bcrypt
        crypt32)

target_link_options(sadx-ap-randomizer PRIVATE
        -static
        -static-libgcc
        -static-libstdc++
        -Wl,--gc-sections)

set_target_properties(sadx-ap-randomizer PROPERTIES PREFIX "" OUTPUT_NAME "sadx-classic-randomizer")
