cmake_minimum_required(VERSION 3.20)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/mingw32.cmake")

project(sadx-ap-randomizer LANGUAGES CXX)

add_library(sadx-ap-randomizer SHARED src/mod.cpp)

target_compile_features(sadx-ap-randomizer PRIVATE cxx_std_17)

target_include_directories(sadx-ap-randomizer PRIVATE
        ${CMAKE_SOURCE_DIR}/lib/windows-header-fix
        ${CMAKE_SOURCE_DIR}/lib/json/include/json
        ${CMAKE_SOURCE_DIR}/lib/APCpp
        ${CMAKE_SOURCE_DIR}/lib/sadx-mod-loader/SADXModLoader/include
        ${CMAKE_SOURCE_DIR}/lib/sadx-mod-loader/mod-loader-common/ModLoaderCommon)

target_compile_definitions(sadx-ap-randomizer PRIVATE
        WIN32
        _WINDOWS
        _USRDLL
        # Non-MSVC workaround: SADXVariables.h still references legacy names.
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:AnimData=AnimData_t>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:PhysicsData=PhysicsData_t>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:AdventureData=AdventureData_t>
        # Skip GCC-incompatible MSVC inline-asm declarations in function headers.
        SADXMODLOADER_SADXFUNCTIONS_H
        SADXMODLOADER_SADXFUNCTIONSNEW_H
)

target_link_options(sadx-ap-randomizer PRIVATE -static-libgcc -static-libstdc++)

set_target_properties(sadx-ap-randomizer PROPERTIES PREFIX "" OUTPUT_NAME "sadx-classic-randomizer")
