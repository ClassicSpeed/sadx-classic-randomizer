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
if not exist ".\Release\sadx-classic-randomizer.dll" (
    echo Source file does not exist: .\Release\sadx-classic-randomizer.dll
    exit /b 1
)

if not exist ".\lib\APCpp\APCpp.dll" (
    echo Source file does not exist: .\lib\APCpp\APCpp.dll
    exit /b 1
)

REM Copy files
copy ".\Release\sadx-classic-randomizer.dll" "!SADX_DIR!\mods\SADX_Archipelago\sadx-classic-randomizer.dll"
copy ".\lib\APCpp\APCpp.dll" "!SADX_DIR!\APCpp.dll"

echo Release files copied successfully.