@echo on

set "VSCMD_START_DIR=%CD%"
call "%VS_PATH%\VC\Auxiliary\Build\vcvars64.bat"

rem Compile the AFF3CT library
cd lib\aff3ct
mkdir %BUILD%
cd %BUILD%
cmake .. -G"Visual Studio 15 2017 Win64" -DCMAKE_CXX_FLAGS="%CFLAGS% /MP%THREADS%" -DAFF3CT_COMPILE_EXE="OFF" -DAFF3CT_COMPILE_STATIC_LIB="ON"
if %ERRORLEVEL% neq 0 exit %ERRORLEVEL%
devenv /build Release aff3ct.sln
if %ERRORLEVEL% neq 0 exit %ERRORLEVEL%
rem devenv /build Release aff3ct.sln /project INSTALL > nul
rem if %ERRORLEVEL% neq 0 exit %ERRORLEVEL%
cd ../../../

mkdir cmake && mkdir cmake/Modules
xcopy lib\aff3ct\%BUILD%\lib\cmake\aff3ct-%AFF3CT_GIT_VERSION%\* cmake\Modules\ /s /e

mkdir %BUILD%
cd %BUILD%
cmake .. -G"Visual Studio 15 2017 Win64" -DCMAKE_CXX_FLAGS="%CFLAGS% /MP%THREADS%"
if %ERRORLEVEL% neq 0 exit %ERRORLEVEL%
devenv /build Release dvbs2_optique.sln
if %ERRORLEVEL% neq 0 exit %ERRORLEVEL%
exit /B 0
