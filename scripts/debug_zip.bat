@echo off
setlocal enabledelayedexpansion

REM Set variables
set OUTPUT_DIR=.\Output
set "APWORLD_DIR=C:\development\workspaces\ArchipelagoMW\worlds\sadx"


REM Create the output directory if it doesn't exist
if not exist %OUTPUT_DIR% mkdir %OUTPUT_DIR%



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
