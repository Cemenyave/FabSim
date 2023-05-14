echo off

cmake -S . -B ./build -G "Ninja" -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=ON
