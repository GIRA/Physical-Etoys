@echo off
color 0A

REM -- Cargo las variables con los parámetros
set target=%1
set port=%2
set uploadRate=%3
set mcu=%4
set fCpu=%5
set programmer=%6

REM -- target es un parámetro obligatorio, indica el nombre del Sketch que vamos a compilar y el nombre del directorio en que está guardado.
if (%target%) == () goto TargetUnspecifiedError

REM -- Configuro algunas variables por defecto para Duemilanove 328 para facilitar las pruebas
if (%uploadRate%) == () set uploadRate=57600
if (%mcu%) == () set mcu=atmega328p
if (%fCpu%) == () set fCpu=16000000
if (%programmer%) == () set programmer=stk500

cd %target%

REM -- Cambio la variable de ambiente PATH y le agrego los directorios donde estan los ejecutables de avr
PUSHD ..\..\hardware\tools\avr\
set PATH=%PATH%;%CD%\bin;%CD%\utils\bin
POPD

REM -- Creo los archivos donde escribir el output y los errores de make
copy nul out
copy nul err

REM -- En el directorio debería existir un archivo Makefile correcto (es responsabilidad de Squeak crearlo)
..\..\hardware\tools\avr\utils\bin\make TARGET=%target% clean
..\..\hardware\tools\avr\utils\bin\make TARGET=%target% applet_files
..\..\hardware\tools\avr\utils\bin\make TARGET=%target% build 2>> err
..\..\hardware\tools\avr\utils\bin\make TARGET=%target% sizeafter 1>> out

REM -- Sólo subo el programa si recibí el port como parámetro
if (%port%) == () goto Finish 
..\..\hardware\tools\avr\utils\bin\make TARGET=%target% PORT=//./%port% UPLOAD_RATE=%uploadRate% AVRDUDE_PROGRAMMER=%programmer% MCU=%mcu% F_CPU=%fCpu% upload 2>> out

:Finish
REM -- Creo el archivo finish para marcar que terminó el proceso
copy nul finish
goto End

:TargetUnspecifiedError
echo Target unspecified
goto End


:End