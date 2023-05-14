echo off

REM cmake -S . -B ./build -G "Visual Studio 17 2022" -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=ON
cmake -S . -B ./build -G "Ninja" -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=ON
