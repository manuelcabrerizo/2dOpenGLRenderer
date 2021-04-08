@echo off

SET INCLUDE_PATH="D:\Dev\tm_renderer\thirdparty\include"
SET LIB_PATH="D:\Dev\tm_renderer\thirdparty\lib"
SET LIBS=gdi32.lib kernel32.lib user32.lib Winmm.lib opengl32.lib glu32.lib strmiids.lib Winmm.lib Xinput.lib Ole32.lib SDL2.lib SDL2_mixer.lib

IF NOT EXIST build mkdir build

pushd build
cl /EHsc /Zi ..\code\*.cpp ..\code\glad.c /Fe:game ^
/I%INCLUDE_PATH% /link /LIBPATH:%LIB_PATH% %LIBS%
popd


