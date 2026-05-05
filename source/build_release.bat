@echo off
setlocal enabledelayedexpansion

echo === GEMS Build Script (Release) ===

:: Получаем путь к папке, где лежит этот bat-файл (то есть source)
set SCRIPT_DIR=%~dp0
:: Убираем завершающий обратный слеш, если есть
if "%SCRIPT_DIR:~-1%"=="\" set SCRIPT_DIR=%SCRIPT_DIR:~0,-1%

:: Родительская папка (GEMS) — это на уровень выше source
for %%i in ("%SCRIPT_DIR%") do set PARENT_DIR=%%~dpi
:: Убираем слеш в конце
if "%PARENT_DIR:~-1%"=="\" set PARENT_DIR=%PARENT_DIR:~0,-1%

set BUILD_DIR=%PARENT_DIR%\build

echo Script dir: %SCRIPT_DIR%
echo Parent dir: %PARENT_DIR%
echo Build dir:  %BUILD_DIR%

:: Удаляем старую папку build, если существует
if exist "%BUILD_DIR%" (
    echo Removing old build directory...
    rmdir /s /q "%BUILD_DIR%"
    if errorlevel 1 (
        echo Failed to remove %BUILD_DIR%
        pause
        exit /b 1
    )
)

:: Создаём новую build папку
mkdir "%BUILD_DIR%"
if errorlevel 1 (
    echo Failed to create %BUILD_DIR%
    pause
    exit /b 1
)

:: Переходим в папку build
cd /d "%BUILD_DIR%"

:: Генерация Makefiles для MinGW (GNU) в Release режиме
echo Running CMake...
cmake "%SCRIPT_DIR%" -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
if errorlevel 1 (
    echo CMake configuration failed.
    pause
    exit /b 1
)

:: Сборка проекта
echo Building project...
cmake --build . --config Release
if errorlevel 1 (
    echo Build failed.
    pause
    exit /b 1
)

echo Build successful! Executable is in %BUILD_DIR%
pause