@echo off
echo ====================================================
echo             WASD-ESOLANG PACKAGING ENGINE           
echo ====================================================

REM 1. Clean out old local development structures
if exist build rmdir /s /q build
if exist wasd-release rmdir /s /q wasd-release

REM 2. Compile high-performance optimized binaries
mkdir build
cd build
cmake .. -G "Ninja" -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
cd ..

REM 3. Verify compilation success before packaging
if not exist build\wasd.exe (
    echo [ERROR]: Compilation failed. Distributable structure canceled.
    exit /b 1
)

REM 4. Generate structured standalone folder directory
echo [INFO]: Staging release directory assets...
mkdir wasd-release
mkdir wasd-release\examples

REM 5. Copy necessary binaries, configurations, and core example scripts
copy build\wasd.exe wasd-release\wasd.exe
copy config.json wasd-release\config.json
copy LICENSE wasd-release\LICENSE
copy examples\hello_world.wasd wasd-release\examples\hello_world.wasd

echo [INFO]: Package assembly successful!
echo Target distribution directory created at: .\wasd-release
echo ====================================================