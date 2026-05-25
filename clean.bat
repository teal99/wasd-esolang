@echo off
cls
echo [INFO]: Cleaning build directory and artifacts...

if exist build (
    rmdir /s /q build
    echo [SUCCESS]: Removed build/ folder.
) else (
    echo [INFO]: Everything looks clean. Nothing to delete.
)