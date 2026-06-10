@echo off
call "C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvars64.bat"
set PATH=C:\vcpkg\installed\x64-windows\debug\bin;C:\vcpkg\installed\x64-windows\bin;%PATH%
set QT_PLUGIN_PATH=C:\vcpkg\installed\x64-windows\Qt6\plugins;C:\vcpkg\installed\x64-windows\debug\Qt6\plugins
cd /d "%~dp0"
build\currency_converter.exe
