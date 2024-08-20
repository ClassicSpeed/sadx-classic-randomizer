@echo off
setlocal enabledelayedexpansion

REM Set variables
set OUTPUT_DIR=.\Output
set VERSION_FILE=.\src\pch.h
set "APWORLD_DIR=C:\development\workspaces\ArchipelagoMW\worlds\sadx"

REM Read version and construct version string
for /F "tokens=3 delims= " %%A in ('findstr /R /C:"^#define SADX_AP_VERSION_MAJOR" %VERSION_FILE%') do set VERSION_MAJOR=%%A
for /F "tokens=3 delims= " %%A in ('findstr /R /C:"^#define SADX_AP_VERSION_MINOR" %VERSION_FILE%') do set VERSION_MINOR=%%A
for /F "tokens=3 delims= " %%A in ('findstr /R /C:"^#define SADX_AP_VERSION_PATCH" %VERSION_FILE%') do set VERSION_PATCH=%%A
set VERSION=%VERSION_MAJOR%.%VERSION_MINOR%.%VERSION_PATCH%


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

REM Create the mod zip file
"C:\Program Files\7-Zip\7z.exe" a -tzip "%OUTPUT_DIR%\SADX_Archipelago_v%VERSION%.zip" "%OUTPUT_DIR%\*" -mx=9 -aoa
copy .\assets\sadx.apworld %OUTPUT_DIR%
copy .\assets\PlayerExample.yaml %OUTPUT_DIR%
@RD /Q /S %OUTPUT_DIR%\SADX_Archipelago


@echo off
set TEMP_DIR=%TEMP%\sadx_temp
set SADX_DIR=%TEMP_DIR%\sadx

rem Create temporary directory structure
mkdir %SADX_DIR%

rem Copy contents to the sadx folder
xcopy "%APWORLD_DIR%\*" "%SADX_DIR%\" /E /I /Y

rem Create the zip file with the sadx folder inside
"C:\Program Files\7-Zip\7z.exe" a -tzip "%OUTPUT_DIR%\sadx.apworld" "%TEMP_DIR%\*" -mx=9 -aoa

rem Clean up temporary directory
rmdir /S /Q %TEMP_DIR%

echo Zip file created at %ZIP_PATH%
