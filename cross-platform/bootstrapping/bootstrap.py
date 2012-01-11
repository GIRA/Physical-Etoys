import platform

from Win32_Bootstrap import Win32_Bootstrap
from Unix_Bootstrap import Unix_Bootstrap

APP_NAME = "PhysicalEtoys"
APP_VERSION = "2.0"

if platform.system() == "Windows":
    b = Win32_Bootstrap(APP_NAME, APP_VERSION)
else:
    b = Unix_Bootstrap(APP_NAME, APP_VERSION)

b.bootstrap()
