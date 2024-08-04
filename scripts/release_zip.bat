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
xcopy .\assets\SADX_Archipelago\ %OUTPUT_DIR%\SADX_Archipelago\ /E /I

REM Update the mod.ini version
echo.>>%OUTPUT_DIR%\SADX_Archipelago\mod.ini
echo Version=%VERSION%>>%OUTPUT_DIR%\SADX_Archipelago\mod.ini

REM Copy files
copy .\Release\sadx-classic-randomizer.dll %OUTPUT_DIR%\SADX_Archipelago\sadx-classic-randomizer.dll

REM Create the zip file
"C:\Program Files\7-Zip\7z.exe" a -tzip "%ZIP_PATH%" "%OUTPUT_DIR%\*" -mx=9 -aoa


copy .\assets\sadx.apworld %OUTPUT_DIR%
copy .\assets\PlayerExample.yaml %OUTPUT_DIR%


@RD /Q /S %OUTPUT_DIR%\SADX_Archipelago

echo Zip file created at %ZIP_PATH%
