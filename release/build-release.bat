REM Get arguments
set BUILDER=%1
if "%1" == "-b" set BUILDER=%2
if "%1" == "--builder" set BUILDER=%2

REM Change current directory to build
cd build

REM Create contents directory and move image, changes and sources
mkdir contents
mv *.image contents/pe.image
mv *.changes contents/pe.changes
mv *.stc contents
mv *.README contents

REM Execute PE release process
@start PhysicalEtoys.exe "%CD%\..\build-release.st" %BUILDER%

REM Change current directory back to release
cd ..