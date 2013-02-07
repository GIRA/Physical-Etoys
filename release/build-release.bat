cd build

REM Create contents directory and move image, changes and sources
mkdir contents
mv *.image contents/pe.image
mv *.changes contents/pe.changes
mv *.stc contents
mv *.README contents

REM Execute PE release process
@start PhysicalEtoys.exe "%CD%\..\build-release.st" %1

cd ..