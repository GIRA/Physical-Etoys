#!/bin/sh
cd build
mkdir contents
mv *.image contents/pe.image
mv *.changes contents/pe.changes
mv *.stc contents

EXE="$PWD/vm"
RES="$PWD/contents"


exec "$EXE/squeakvm" \
	-plugins "$EXE" \
	-encoding latin1 \
	-vm-display-X11  \
	"$RES/pe.image" \
	"$PWD/../build-release.st"
