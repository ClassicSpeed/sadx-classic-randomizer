@echo off
setlocal enabledelayedexpansion

REM SADX folder to copy dlls
set "SADX_DIR=C:\Program Files (x86)\Steam\steamapps\common\Sonic Adventure DX"

REM Check if SADX_DIR exists
if not exist "!SADX_DIR!" (
    echo Output directory does not exist: "!SADX_DIR!"
    exit /b 1
)

REM Check if source files exist
if not exist ".\Debug\sadx-classic-randomizer.dll" (
    echo Source file does not exist: .\Debug\sadx-classic-randomizer.dll
    exit /b 1
)


REM Copy files
if not exist "!SADX_DIR!\mods\SADX_Archipelago" mkdir "!SADX_DIR!\mods\SADX_Archipelago"
copy ".\Debug\sadx-classic-randomizer.dll" "!SADX_DIR!\mods\SADX_Archipelago\sadx-classic-randomizer.dll"
echo Debugs files copied successfully.