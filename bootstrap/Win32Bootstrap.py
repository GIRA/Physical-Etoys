import os
import subprocess
import platform

import configure
from GenericBootstrap import GenericBootstrap

class Win32Bootstrap(GenericBootstrap):

    PLATFORM = "Windows"
    WINDOWS_VM_NAME = "VM.win32.2"

    def installVM(self):
        url = self.PE_BASE_REPO + self.WINDOWS_VM_NAME + ".tar.gz"
        downloadedFile = self.downloadTo(self.tmpDir(), url)
        print("Extracting VM...")
        self.extractTo(self.appDir(), downloadedFile)
    
    def installArduinoStuff(self):
        print "TODO: Installing arduino stuff for Windows..."

    def installNxtStuff(self):
        print "TODO: Installing nxt stuff for Windows..."

    def installPE(self):
        print("Bootstrapping the image. Wait for Squeak to close itself automatically.")
        #Take the .ini file out because it bothers the script execution
        if os.path.exists(os.path.join(self.tmpDir(), "PhysicalEtoys.ini")):
            os.remove(os.path.join(self.tmpDir(), "PhysicalEtoys.ini"))
        self.moveMatchingFiles("PhysicalEtoys.ini", \
                               self.appDir(), \
                               self.tmpDir())
        #Execute PhysicalEtoys with the startup script

        self.run(os.path.join(self.appDir(), "PhysicalEtoys"), \
                  [os.path.join(self.absAppDir() , "Content", self.appName + ".image"), \
                   os.path.join(os.getcwd(), "install_pe.st")])

        #Move the .ini file back
        if os.path.exists(os.path.join(self.appDir(), "PhysicalEtoys.ini")):
            os.remove(os.path.join(self.appDir(), "PhysicalEtoys.ini"))
        self.moveMatchingFiles("PhysicalEtoys.ini", \
                               self.tmpDir(), \
                               self.appDir())

    def package(self):
        configure.configure(self, os.path.join("win32", "physicaletoys.nsi.in"), os.path.join(self.tmpDir(), "physicaletoys.nsi"))

    def run(self, app, params):
        """ Launch an application, using wine when running on Linux.
        """

        cmd = [app] + params

        if platform.system() != "Windows":
            print("Not running on Windows!")
            if not self.which("wine"):
                raise Exception("WINE is not installed. Install it to cross-compile to Windows.")
            else:
                print("Trying with wine...")
                cmd = ["wine"] + cmd

        subprocess.Popen(cmd).wait()
