@echo off
setlocal

set "source=C:/dev/CrystalX/bin/windows_x86_64-Debug/CrystalX"
set "destination=C:/dev/CrystalX/bin/windows_x86_64-Debug/SandBox"

:: copying .dll files
copy "%source%\*.dll" "%destination%"

echo Done.
endlocal