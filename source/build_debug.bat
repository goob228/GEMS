@echo off
setlocal enabledelayedexpansion

echo === GEMS Build Script (Debug) ===

:: Получаем путь к папке, где лежит этот bat-файл (то есть source)
set SCRIPT_DIR=%~dp0
:: Убираем завершающий обратный слеш, если есть
if "%SCRIPT_DIR:~-1%"=="\" set SCRIPT_DIR=%SCRIPT_DIR:~0,-1%

:: Родительская папка (GEMS) — это на уровень выше source
for %%i in ("%SCRIPT_DIR%") do set PARENT_DIR=%%~dpi
:: Убираем слеш в конце
if "%PARENT_DIR:~-1%"=="\" set PARENT_DIR=%PARENT_DIR:~0,-1%

set BUILD_DIR=%PARENT_DIR%\build_debug

echo Script dir: %SCRIPT_DIR%
echo Parent dir: %PARENT_DIR%
echo Build dir:  %BUILD_DIR%

:: Удаляем старую папку build_debug, если существует
if exist "%BUILD_DIR%" (
    echo Removing old build directory...
    rmdir /s /q "%BUILD_DIR%"
    if errorlevel 1 (
        echo Failed to remove %BUILD_DIR%
        pause
        exit /b 1
    )
)

:: Создаём новую build_debug папку
mkdir "%BUILD_DIR%"
if errorlevel 1 (
    echo Failed to create %BUILD_DIR%
    pause
    exit /b 1
)

:: Переходим в папку build_debug
cd /d "%BUILD_DIR%"

:: Генерация Makefiles для MinGW (GNU) в Debug режиме
echo Running CMake...
cmake "%SCRIPT_DIR%" -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug
if errorlevel 1 (
    echo CMake configuration failed.
    pause
    exit /b 1
)

:: Сборка проекта
echo Building project...
cmake --build . --config Debug
if errorlevel 1 (
    echo Build failed.
    pause
    exit /b 1
)

:: Опционально: копирование Debug-версий DLL SFML (раскомментируйте, если нужно)
:: set SFML_BIN=C:\Modules\SFML-3.1.0\bin
:: if exist "%BUILD_DIR%\GEMS.exe" (
::     echo Copying SFML Debug DLLs...
::     copy "%SFML_BIN%\sfml-graphics-d-3.dll" "%BUILD_DIR%\" >nul
::     copy "%SFML_BIN%\sfml-window-d-3.dll"   "%BUILD_DIR%\" >nul
::     copy "%SFML_BIN%\sfml-system-d-3.dll"   "%BUILD_DIR%\" >nul
::     echo DLLs copied.
:: )

echo Build successful! Executable is in %BUILD_DIR%
pause