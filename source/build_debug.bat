if exist Debug rmdir /s /q Debug
mkdir Debug
cd Debug
cmake .. -DCMAKE_BUILD_TYPE=Debug -G "MinGW Makefiles"
cmake --build . --config Debug
pause