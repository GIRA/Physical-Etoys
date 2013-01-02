#!/bin/sh
cd build

# Create contents directory and move image, changes and sources
mkdir contents
mv *.image contents/pe.image
mv *.changes contents/pe.changes
mv *.stc contents
mv *.README contents

# Execute PE release process
EXE="$PWD/vm"
RES="$PWD/contents"
"$EXE/squeakvm" \
	-plugins "$EXE" \
	-encoding latin1 \
	-vm-display-X11 \
	"$RES/pe.image" \
	"$PWD/../build-release.st" \
	$1

# Change permissions of executable files
chmod ugo+x "$RES/Arduino/Sketches/upload.sh"
chmod ugo+x "$RES/Arduino/hardware/tools/avr/bin/avrdude"
chmod ugo+x "$RES/Arduino/hardware/tools/hid_bootcli/v1.0/hid_bootloader_cli.Linux"