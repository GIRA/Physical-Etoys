#!/bin/sh

#Cargo las variables con los parámetros
target=$1
port=$2
uploadRate=$3
mcu=$4
fCpu=$5
programmer=$6

#Configuro las variables por defecto para Duemilanove
if [ -z $uploadRate ]
then
    uploadRate=57600
fi
if [ -z $mcu ]
then
    mcu=atmega328p
fi
if [ -z $fCpu ]
then
    fCpu=16000000
fi
if [ -z $programmer ]
then
    programmer=stk500
fi

#Creo los archivos donde escribir el output y los errores de make
> $target/err
> $target/out

#En el directorio debería existir un archivo Makefile correcto (es responsabilidad de Squeak crearlo)
if [ -f clean ]; then
    make -s -C $target clean "TARGET=$target"
fi
make -s -C $target applet_files "TARGET=$target"
make -s -C $target build "TARGET=$target" 2> $target/err
make -s -C $target sizeafter "TARGET=$target" 1> $target/out

#Sólo subo el programa si recibí el port como parámetro
if [ ! -z $port ]
then
    make -s -C $target upload "TARGET=$target" "PORT=$port" "UPLOAD_RATE=$uploadRate" "AVRDUDE_PROGRAMMER=$programmer" "MCU=$mcu" "F_CPU=$fCpu" 2> $target/out
fi

#Creo el archivo finish para marcar que terminó el proceso
> $target/finish

