@echo off
cls
echo ====================================================
echo               BUILDING WASD-LANG COMPILER            
echo ====================================================

if not exist build (
    mkdir build
)

echo [INFO]: Configuring CMake files...
cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
if %ERRORLEVEL% NEQ 0 (
    echo [ERROR]: CMake configuration failed!
    exit /b %ERRORLEVEL%
)

echo.
echo [INFO]: Compiling binaries...
cmake --build build --config Release
if %ERRORLEVEL% NEQ 0 (
    echo [ERROR]: Compilation build failed!
    exit /b %ERRORLEVEL%
)

echo.
echo [SUCCESS]: Done! Binary built inside build/wasd.exe