#! /usr/bin/env python

APP_NAME = "PhysicalEtoys"
APP_VERSION = "2.0"

print("Welcome to the PhysicalEtoys bootstrapper\n"
      "=========================================\n\n"
      "What is your target platform?\n"
      "w) Windows (.exe)\n"
      "d) Ubuntu/Debian (.deb)\n"
      "u) Generic Unixes (.tar.gz)\n"
      "\n"
      "a) Build all targets\n")
platform = raw_input("Enter a letter: ")

if platform.lower() in "aw":
    from bootstrap.Win32Bootstrap import Win32Bootstrap
    Win32Bootstrap(APP_NAME, APP_VERSION).bootstrap()

if platform.lower() in "da":
    print("Debian package generation not yet supported :-( Falling back to tar.gz.")

if platform.lower() in "dua":
    from bootstrap.UnixBootstrap import UnixBootstrap
    UnixBootstrap(APP_NAME, APP_VERSION).bootstrap()
