call "C:\Program Files\Microsoft Visual Studio 9.0\VC\vcvarsall.bat"
cd vs2008

msbuild moai.sln /t:Clean,Build /property:Config=Debug-Lua-5.1
if ERRORLEVEL 1 exit

msbuild moai.sln /t:Clean,Build /property:Config=Release-Lua-5.1
if ERRORLEVEL 1 exit

msbuild moai.sln /t:Clean,Build /property:Config=Debug-Lua-5.2
if ERRORLEVEL 1 exit

msbuild moai.sln /t:Clean,Build /property:Config=Release-Lua-5.2
if ERRORLEVEL 1 exit

msbuild moai.sln /t:Clean,Build /property:Config=Debug-LuaJIT
if ERRORLEVEL 1 exit

msbuild moai.sln /t:Clean,Build /property:Config=Release-LuaJIT
if ERRORLEVEL 1 exit