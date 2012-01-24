import os
import subprocess

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
        subprocess.Popen([os.path.join(self.appDir(), "PhysicalEtoys"), \
                          os.path.join(self.absAppDir() , "Content", self.appName + ".image"), \
                          os.path.join(os.getcwd(), "install_pe.st")]).wait()
        #Move the .ini file back
        if os.path.exists(os.path.join(self.appDir(), "PhysicalEtoys.ini")):
            os.remove(os.path.join(self.appDir(), "PhysicalEtoys.ini"))
        self.moveMatchingFiles("PhysicalEtoys.ini", \
                               self.tmpDir(), \
                               self.appDir())
