@echo off
cls
echo ====================================================
echo               WASD-LANG DEVELOPMENT PIPELINE        
echo ====================================================

echo [STEP 1/3]: Cleaning workspace...
call clean.bat
echo.

echo [STEP 2/3]: Compiling codebase...
call build.bat
if %ERRORLEVEL% NEQ 0 (
    echo.
    echo [ERROR]: Dev pipeline aborted due to a compilation failure!
    exit /b %ERRORLEVEL%
)
echo.

echo [STEP 3/3]: Launching target program...
echo ----------------------------------------------------
if "%~1"=="" (
    call run.bat
) else (
    call run.bat %1
)