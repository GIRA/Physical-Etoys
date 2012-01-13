import platform

from Win32Bootstrap import Win32Bootstrap
from UnixBootstrap import UnixBootstrap

APP_NAME = "PhysicalEtoys"
APP_VERSION = "2.0"

if platform.system() == "Windows":
    b = Win32Bootstrap(APP_NAME, APP_VERSION)
else:
    b = UnixBootstrap(APP_NAME, APP_VERSION)

b.bootstrap()
