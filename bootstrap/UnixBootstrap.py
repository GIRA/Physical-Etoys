import os
import subprocess
import tarfile

from GenericBootstrap import GenericBootstrap

class UnixBootstrap(GenericBootstrap):
    
    PLATFORM = "Unix"
    UNIX_VM_NAME = "VM.unix.1"

    def installVM(self):
        url = self.PE_BASE_REPO + self.UNIX_VM_NAME + ".tar.gz"
        downloadedFile = self.downloadTo(self.tmpDir(), url)
        print("Extracting VM...")
        self.extractTo(os.path.join(self.appDir(), "vm"), downloadedFile)
    
    def installArduinoStuff(self):
        print "TODO: Installing arduino stuff for Linux..."

    def installNxtStuff(self):
        print "TODO: Installing nxt stuff for Linux..."

    def installPE(self):
        print("Bootstrapping the image. Wait for Squeak to close itself automatically.")
        subprocess.Popen(["squeak", \
                          os.path.join(self.appDir(), "content", "pe.image"), \
                          os.path.join(os.getcwd(), "install_pe.st")]) .wait()

    def package(self):
        print("Creating the tar.gz package...")

        tarfile.open(os.path.join(self.appDir(), self.appNameBase() + ".tar.gz"), "w:gz").add(os.path.join(self.appDir(), "content"), arcname = self.appNameBase())
        print(self.appNameBase() + ".tar.gz successfully created in " + self.appDir() + ".")

