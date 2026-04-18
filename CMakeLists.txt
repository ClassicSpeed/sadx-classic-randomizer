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

option(SADX_SIZE_OPTIMIZED_RELEASE "Enable size-oriented flags for Release/MinSizeRel builds" ON)

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
        ${CMAKE_SOURCE_DIR}/lib/windows-header-fix
        ${CMAKE_SOURCE_DIR}/lib/APCpp
        ${CMAKE_SOURCE_DIR}/lib/APCpp/IXWebSocket
        ${CMAKE_SOURCE_DIR}/lib/APCpp/jsoncpp/include)

set(MOD_LOADER_INCLUDE_DIRS
        ${CMAKE_SOURCE_DIR}/lib/sadx-mod-loader-linux-compatible/ModLoaderCommon
        ${CMAKE_SOURCE_DIR}/lib/sadx-mod-loader-linux-compatible)

set(COMMON_COMPILE_DEFINITIONS WIN32 _WINDOWS _USRDLL UNICODE _UNICODE)

# ModLoader Common
add_library(mod-loader-common STATIC
        lib/sadx-mod-loader-linux-compatible/ModLoaderCommon/IniFile.cpp
        lib/sadx-mod-loader-linux-compatible/ModLoaderCommon/TextConv.cpp)
target_compile_features(mod-loader-common PRIVATE cxx_std_17)
target_include_directories(mod-loader-common PRIVATE ${COMMON_INCLUDE_DIRS})
target_include_directories(mod-loader-common SYSTEM PRIVATE ${MOD_LOADER_INCLUDE_DIRS})
target_compile_definitions(mod-loader-common PRIVATE ${COMMON_COMPILE_DEFINITIONS})


# SADX AP Configurations
add_library(sadx-ap-randomizer-configuration OBJECT ${CONFIGURATION_SOURCES})
target_compile_features(sadx-ap-randomizer-configuration PRIVATE cxx_std_17)
target_include_directories(sadx-ap-randomizer-configuration PRIVATE ${COMMON_INCLUDE_DIRS})
target_include_directories(sadx-ap-randomizer-configuration SYSTEM PRIVATE ${MOD_LOADER_INCLUDE_DIRS})
target_compile_definitions(sadx-ap-randomizer-configuration PRIVATE ${COMMON_COMPILE_DEFINITIONS})

if(SADX_SIZE_OPTIMIZED_RELEASE)
    target_compile_options(sadx-ap-randomizer-configuration PRIVATE
            $<$<CONFIG:Release>:-ffunction-sections -fdata-sections>
            $<$<CONFIG:MinSizeRel>:-ffunction-sections -fdata-sections>)
endif()


# SADX AP Randomizer Core
add_library(sadx-ap-randomizer-core OBJECT
        src/mod.cpp
        lib/APCpp/Archipelago.cpp
        lib/APCpp/Archipelago_DataStorageSim.cpp
        lib/APCpp/Archipelago_Gifting.cpp
        src/output/reactionManager/ReactionManager.cpp
        src/output/characterManager/CharacterManager.cpp
        src/output/itemRepository/ItemRepository.cpp
        src/output/locationRepository/LocationRepository.cpp
        src/output/archipelagoMessenger/ArchipelagoMessenger.cpp
        src/output/saveFileManager/SaveFileManager.cpp
        src/output/musicManager/MusicManager.cpp
        src/output/worldStateManager/WorldStateManager.cpp
        src/output/worldStateManager/setObjectManager/SetObjectManager.cpp
        src/output/worldStateManager/adventureFieldEntranceManager/AdventureFieldEntranceManager.cpp
        src/output/worldStateManager/adventureFieldEntranceManager/AdventureFieldEntranceMap.cpp
        src/output/worldStateManager/adventureFieldEntranceManager/mapManager/MapManager.cpp
        src/application/randomizer/Randomizer.cpp
        src/application/link/Link.cpp
        src/input/cheatsManager/CheatsManager.cpp
        src/input/archipelago/ArchipelagoManager.cpp
        src/input/eventDetector/EventDetector.cpp
        src/input/characterLoading/CharacterLoadingDetector.cpp
        src/output/displayManager/DisplayManager.cpp)
add_dependencies(sadx-ap-randomizer-core sadx-ap-randomizer-configuration)
target_compile_features(sadx-ap-randomizer-core PRIVATE cxx_std_17)
target_include_directories(sadx-ap-randomizer-core PRIVATE ${COMMON_INCLUDE_DIRS})
target_include_directories(sadx-ap-randomizer-core SYSTEM PRIVATE ${MOD_LOADER_INCLUDE_DIRS})
target_compile_definitions(sadx-ap-randomizer-core PRIVATE ${COMMON_COMPILE_DEFINITIONS})
target_compile_options(sadx-ap-randomizer-core PRIVATE -fpermissive)

if(SADX_SIZE_OPTIMIZED_RELEASE)
    target_compile_options(sadx-ap-randomizer-core PRIVATE
            $<$<CONFIG:Release>:-ffunction-sections -fdata-sections>
            $<$<CONFIG:MinSizeRel>:-ffunction-sections -fdata-sections>)
endif()

add_library(sadx-ap-randomizer SHARED
        $<TARGET_OBJECTS:sadx-ap-randomizer-configuration>
        $<TARGET_OBJECTS:sadx-ap-randomizer-core>)

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

if(SADX_SIZE_OPTIMIZED_RELEASE)
    target_link_options(sadx-ap-randomizer PRIVATE
            -static
            -static-libgcc
            -static-libstdc++
            $<$<CONFIG:Release>:-Wl,--gc-sections -s>
            $<$<CONFIG:MinSizeRel>:-Wl,--gc-sections -s>)
else()
    target_link_options(sadx-ap-randomizer PRIVATE -static -static-libgcc -static-libstdc++)
endif()

set_target_properties(sadx-ap-randomizer PROPERTIES PREFIX "" OUTPUT_NAME "sadx-classic-randomizer")
