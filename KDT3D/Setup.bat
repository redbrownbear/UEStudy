@echo off
REM REM은 주석을, echo 할말은 Text출력을, echo.은 enter를 의미한다.
echo [vcpkg task]
echo.
call ./ThirdParty/vcpkg/bootstrap-vcpkg.bat
.\ThirdParty\vcpkg\vcpkg.exe install rapidjson
.\ThirdParty\vcpkg\vcpkg.exe install boost:x64-windows
.\ThirdParty\vcpkg\vcpkg.exe integrate install

pause