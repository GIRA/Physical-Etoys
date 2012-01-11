import os
import subprocess

from PE_Bootstrap import PE_Bootstrap

class Unix_Bootstrap(PE_Bootstrap):
    
    def installVM(self):
        """Does nothing"""
    
    def installArduinoStuff(self):
        print "To do: Installing arduino stuff for Linux..."

    def installNxtStuff(self):
        print "To do: Installing nxt stuff for Linux..."

    def installPE(self):
        print("Bootstrapping the image. Wait for Squeak to close itself automatically.")
        subprocess.Popen(["squeak", \
                          os.path.join(self.appDir(), "Content", self.appName + ".image"), \
                          os.path.join(os.getcwd(), "install_pe.st")]) .wait()
