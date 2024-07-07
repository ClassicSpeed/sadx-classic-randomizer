@echo off
setlocal enabledelayedexpansion

REM Set variables
set OUTPUT_DIR=.\Output
set VERSION_FILE=.\src\pch.h

REM Read version and construct version string
for /F "tokens=3 delims= " %%A in ('findstr /R /C:"^#define SADX_AP_VERSION_MAJOR" %VERSION_FILE%') do set VERSION_MAJOR=%%A
for /F "tokens=3 delims= " %%A in ('findstr /R /C:"^#define SADX_AP_VERSION_MINOR" %VERSION_FILE%') do set VERSION_MINOR=%%A
for /F "tokens=3 delims= " %%A in ('findstr /R /C:"^#define SADX_AP_VERSION_PATCH" %VERSION_FILE%') do set VERSION_PATCH=%%A
set VERSION=%VERSION_MAJOR%.%VERSION_MINOR%.%VERSION_PATCH%

REM Construct the zip file name
set ZIP_PATH=%OUTPUT_DIR%\SADX_Archipelago_v%VERSION%.zip

REM Create the output directory if it doesn't exist
if not exist %OUTPUT_DIR% mkdir %OUTPUT_DIR%
if not exist %OUTPUT_DIR%\SADX_Archipelago  mkdir %OUTPUT_DIR%\SADX_Archipelago 


REM Copy other required files (example: readme.txt, config files)
copy .\assets\SADX_Archipelago\ %OUTPUT_DIR%\SADX_Archipelago\ 

REM Update the mod.ini version
echo.>>%OUTPUT_DIR%\SADX_Archipelago\mod.ini
echo Version=%VERSION%>>%OUTPUT_DIR%\SADX_Archipelago\mod.ini

REM Copy files
copy .\Release\sadx-classic-randomizer.dll %OUTPUT_DIR%\SADX_Archipelago\sadx-classic-randomizer.dll
copy .\lib\APCpp\APCpp.dll %OUTPUT_DIR%\SADX_Archipelago\APCpp.dll

REM Create the zip file
powershell Compress-Archive -Path %OUTPUT_DIR%\* -DestinationPath %ZIP_PATH% -Force


copy .\assets\sadx.apworld %OUTPUT_DIR%
copy .\assets\PlayerExample.yaml %OUTPUT_DIR%


@RD /Q /S %OUTPUT_DIR%\SADX_Archipelago

echo Zip file created at %ZIP_PATH%
