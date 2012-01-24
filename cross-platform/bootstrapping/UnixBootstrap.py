import os
import subprocess
import tarfile

from GenericBootstrap import GenericBootstrap

class UnixBootstrap(GenericBootstrap):
    
    PLATFORM = "Unix"

    def installVM(self):
        if not self.which("squeak"):
            print("It seems that 'squeak' is not installed on your system.\n"
                  "You can probably install it with your package manager.\n"
                  "On Ubuntu, enter 'sudo apt-get install squeak-vm' to install it.")
    
    def installArduinoStuff(self):
        print "TODO: Installing arduino stuff for Linux..."

    def installNxtStuff(self):
        print "TODO: Installing nxt stuff for Linux..."

    def installPE(self):
        print("Bootstrapping the image. Wait for Squeak to close itself automatically.")
        subprocess.Popen(["squeak", \
                          os.path.join(self.appDir(), "Content", self.appName + ".image"), \
                          os.path.join(os.getcwd(), "install_pe.st")]) .wait()
