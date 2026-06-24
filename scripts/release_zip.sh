#!/bin/bash
set -e

# Set variables
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$(dirname "$SCRIPT_DIR")"
OUTPUT_DIR="$PROJECT_DIR/Output"
VERSION_FILE="$PROJECT_DIR/src/pch.h"
DLL_DIR="/home/classic/Documents/development/workspaces/sadx-classic-randomizer/Release"
APWORLD_SRC="/home/classic/Documents/development/workspaces/Archipelago/build/apworlds/sadx.apworld"

# Read version and construct version string
VERSION_MAJOR=$(grep -P "^#define SADX_AP_VERSION_MAJOR" "$VERSION_FILE" | awk '{print $3}')
VERSION_MINOR=$(grep -P "^#define SADX_AP_VERSION_MINOR" "$VERSION_FILE" | awk '{print $3}')
VERSION_PATCH=$(grep -P "^#define SADX_AP_VERSION_PATCH" "$VERSION_FILE" | awk '{print $3}')
VERSION="$VERSION_MAJOR.$VERSION_MINOR.$VERSION_PATCH"

echo "Building version $VERSION..."

# Create output directories
mkdir -p "$OUTPUT_DIR/SADX_Archipelago"

# Copy assets
cp -r "$PROJECT_DIR/assets/SADX_Archipelago/." "$OUTPUT_DIR/SADX_Archipelago/"

# Update the mod.ini version
echo "" >> "$OUTPUT_DIR/SADX_Archipelago/mod.ini"
echo "Version=$VERSION" >> "$OUTPUT_DIR/SADX_Archipelago/mod.ini"

# Copy DLL
cp "$DLL_DIR/sadx-classic-randomizer.dll" "$OUTPUT_DIR/SADX_Archipelago/sadx-classic-randomizer.dll"

# Create the mod zip file
cd "$OUTPUT_DIR"
zip -r -9 "SADX_Archipelago_v$VERSION.zip" "SADX_Archipelago"
cd "$PROJECT_DIR"

# Clean up SADX_Archipelago folder
rm -rf "$OUTPUT_DIR/SADX_Archipelago"

# Copy the apworld file
cp "$APWORLD_SRC" "$OUTPUT_DIR/sadx.apworld"

echo "Done! Output in $OUTPUT_DIR"