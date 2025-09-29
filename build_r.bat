@echo off
setlocal enabledelayedexpansion

echo ========================================
echo    Building Bank System (Static Link)
echo ========================================
echo.

:: Проверяем компилятор
where g++ >nul 2>nul
if errorlevel 1 (
    echo ERROR: g++ not found in PATH
    echo Please install MinGW or add to PATH
    pause
    exit /b 1
)

echo Step 1: Creating build directory...
if not exist build mkdir build

echo.
echo Step 2: Compiling source files...

set SOURCES=baseEntity.cpp account.cpp card.cpp creditRequest.cpp encryption.cpp transaction.cpp user.cpp uuid.cpp bank_system.cpp

set ERROR_COUNT=0
for %%f in (%SOURCES%) do (
    if exist "src\core\src\%%f" (
        echo Compiling %%f...
        g++ -std=c++17 -I.\src\core\include -c "src\core\src\%%f" -o "build\%%~nf.obj"
        if !errorlevel! neq 0 (
            echo Failed to compile %%f
            set /a ERROR_COUNT+=1
        ) else (
            echo %%f compiled
        )
    ) else (
        echo File src\core\src\%%f not found
        set /a ERROR_COUNT+=1
    )
)

if %ERROR_COUNT% gtr 0 (
    echo.
    echo %ERROR_COUNT% files failed to compile
    pause
    exit /b 1
)

echo.
echo Step 3: Compiling main.cpp...
g++ -std=c++17 -I.\src\core\include -c "src\main.cpp" -o "build\main.obj"
if errorlevel 1 (
    echo Failed to compile main.cpp
    pause
    exit /b 1
)

echo.
echo Step 4: Linking with static libraries...
g++ -std=c++17 -static -static-libgcc -static-libstdc++ build\*.obj -o build\bank_app.exe
if errorlevel 1 (
    echo Linking failed
    pause
    exit /b 1
)

echo.
echo Step 5: Checking executable...
if exist build\bank_app.exe (
    echo bank_app.exe created successfully!
    echo Size: %~z0 bytes
    echo Static linking: No external DLLs required
) else (
    echo Executable not created
    pause
    exit /b 1
)

echo.
echo ========================================
echo    BUILD SUCCESSFUL!
echo ========================================
echo.
echo You can now run: build\bank_app.exe
echo The executable is standalone - no DLLs required!
pause