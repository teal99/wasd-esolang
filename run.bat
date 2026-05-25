@echo off
cls
echo ====================================================
echo                EXECUTING WASD-LANG CODE             
echo ====================================================

if not exist "build\wasd.exe" (
    echo [WARN]: wasd.exe not found! Running build first...
    call build.bat
    echo.
)

if "%~1"=="" (
    echo [INFO]: No file provided. Running default example...
    if exist "examples\hello_world.wasd" (
        build\wasd.exe .\examples\hello_world.wasd
    ) else (
        echo [ERROR]: Target example file 'examples\hello_world.wasd' does not exist!
        echo Usage: run.bat [path_to_your_file.wasd]
    )
) else (
    build\wasd.exe %1
)