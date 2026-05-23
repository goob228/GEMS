if exist Release rmdir /s /q Release
mkdir Release
cd Release
cmake .. -DCMAKE_BUILD_TYPE=Release -G "MinGW Makefiles"
cmake --build . --config Release
pause