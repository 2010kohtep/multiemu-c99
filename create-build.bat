@echo off
set BUILD_DIR=build
if not exist %BUILD_DIR% (
    mkdir %BUILD_DIR%
    echo Created directory: %BUILD_DIR%
)
cd %BUILD_DIR%
cmake -A Win32 ..