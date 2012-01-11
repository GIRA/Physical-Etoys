import os
import subprocess

from PE_Bootstrap import PE_Bootstrap

class Win32_Bootstrap(PE_Bootstrap):

    def installVM(self):
        repo = "https://github.com/downloads/GIRA/Physical-Etoys/"
        fileName = "VM.win32.2"
        url = repo + fileName + ".tar.gz"
        downloadedFile = self.downloadTo(self.tmpDir(), url)
        print("Extracting VM...")
        self.extractTo(self.appDir(), downloadedFile)
    
    def installArduinoStuff(self):
        print "To do: Installing arduino stuff for Windows..."

    def installNxtStuff(self):
        print "To do: Installing nxt stuff for Windows..."

    def installPE(self):
        print("Bootstrapping the image. Wait for Squeak to close itself automatically.")
        #Take the .ini file out because it bothers the script execution
        self.moveMatchingFiles("PhysicalEtoys.ini", \
                               self.appDir(), \
                               self.tmpDir())                              
        subprocess.Popen([os.path.join(self.appDir(), "PhysicalEtoys"), \
                          os.path.join(self.absAppDir() , "Content", self.appName + ".image"), \
                          os.path.join(os.getcwd(), "install_pe.st")]).wait()
        #Move the .ini file back
        self.moveMatchingFiles("PhysicalEtoys.ini", \
                               self.tmpDir(), \
                               self.appDir())
