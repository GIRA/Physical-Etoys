import os
import sys

import urllib2
import tarfile
import shutil
import glob

class GenericBootstrap:
    
    PLATFORM = "Undefined"

    ETOYS_REPO = "http://download.sugarlabs.org/sources/sucrose/glucose/etoys/"
    ETOYS_NAME = "etoys-4.1.2390"
    
    PE_BASE_REPO = "https://github.com/downloads/GIRA/Physical-Etoys/"
    PE_BASE_NAME = "fresca.etoys.32"
            
    def __init__(self, appName, appVersion):
        self.appName = appName
        self.appVersion = appVersion
        if os.path.exists(self.appDir()):
            print("Attention: " + self.appDir() + " already exists!")
            r = raw_input("What should I do?\n\t'o':overwrite\n\t'c':cancel\n")
            if r != 'o':
                print("Cancelling.")
                sys.exit(1)
            #Delete previous version
            shutil.rmtree(self.appDir())
        self.makeDir(self.appDir())
        self.makeDir(self.tmpDir())
        self.configureProxy()

    def bootstrap(self):
        print("*** " + self.appName + " " + self.appVersion + " bootstrapping ***\n")
        self.installVM()
        self.installImage()
        self.installLocale()
        self.installTutorials()
        self.installArduinoStuff()
        self.installNxtStuff()
        self.installPE()
        print("***** We are done! ******")

    #Accessing:
    def appNameBase(self):
        return self.appName + '-' + str(self.appVersion)

    def appDir(self):
        return os.path.join('.', self.appNameBase() + '-' + self.PLATFORM)


    def absAppDir(self):
        return os.path.join(os.getcwd(), self.appDir())
   
    def tmpDir(self):
        return os.path.join('.', self.appName + '.' + str(self.appVersion) + '.Tmp')

    #Cross-platform:
    def installImage(self):
        self.makeDir(os.path.join(self.appDir(), 'Content'))

        url = self.PE_BASE_REPO + self.PE_BASE_NAME + ".tar.gz"
        downloadedFile = self.downloadTo(self.tmpDir(), url)
        print("Extracting image...")
        self.extractTo(self.tmpDir(), downloadedFile)
        print("Copying and renaming files...")
        self.moveAndRenameImage(self.tmpDir(), \
                                os.path.join(self.appDir(), 'Content'))
            
    def installLocale(self):
        url = self.ETOYS_REPO + self.ETOYS_NAME + ".tar.gz"
        downloadedFile = self.downloadTo(self.tmpDir(), url)
        print("Extracting locale...")
        self.extractTo(self.tmpDir(), downloadedFile)
        print("Copying locale files...")
        self.moveSupportedLocales(os.path.join(self.tmpDir(), self.ETOYS_NAME, 'Content', 'locale'), \
                                  os.path.join(self.appDir(), 'Content', 'locale'))
        
    def installTutorials(self):
        print "TODO: Installing tutorials..."


        
    # Platform-specific:
    def installVM(self):
        raise Exception("Not implemented")
    
    def installArduinoStuff(self):
        raise Exception("Not implemented")
    
    def installNxtStuff(self):
        raise Exception("Not implemented")
    
    def installPE(self):
        """Run squeak with the install_pe script"""
        raise Exception("Not implemented")


    #Utils:
    def configureProxy(self):
        """ If the file is empty, it assumes no proxy
        """
        proxies = urllib2.getproxies()
        proxy_config = open("proxy.config", "w+")
        if 'http' in proxies.keys():
            proxy_config.write(proxies['http'].split('/')[-1])
        proxy_config.close()        
    
    def makeDir(self, path):
        if not os.path.exists(path):
            os.mkdir(path)

    def moveMatchingFiles(self, match, from_dir, to_dir):
        for file in glob.glob(os.path.join(from_dir, match)):
            shutil.move(file, to_dir)
        
    def moveAndRenameImage(self, from_dir, to_dir):
        self.moveMatchingFiles("*.image", \
                               from_dir, \
                               os.path.join(to_dir, self.appName + ".image"))
        self.moveMatchingFiles("*.changes", \
                               from_dir, \
                               os.path.join(to_dir, self.appName + ".changes"))

    def moveDir(self, from_dir, to_dir):
        shutil.move(from_dir, to_dir)

    def moveSupportedLocales(self, from_dir, to_dir):
        """ It only moves the .mo files, it ignores Quickguides
        """
        for each in ["en", "es", "fr", "pt", "pt_BR"]:
            self.moveDir(os.path.join(from_dir, each, 'LC_MESSAGES'), \
                         os.path.join(to_dir, each, 'LC_MESSAGES'))
        
    def extractTo(self, dest, tar_file):
        tarfile.open(tar_file).extractall(dest)
        
    def downloadTo(self, dest, url, local = '.'):
        def privateDownload(url, file_name, reporthook):
            """Added because urllib.urlretrieve() wasn't working with https
            """
            u = urllib2.urlopen(url)
            f = open(file_name, 'wb')
            meta = u.info()
            bs = 1024*8
            size = int(meta.getheaders("Content-Length")[0])
            read = 0
            blocknum = 0
            reporthook(blocknum, bs, size)
            while 1:
                block = u.read(bs)
                if block == "":
                    break
                read += len(block)
                f.write(block)
                blocknum += 1
                reporthook(blocknum, bs, size)        
            f.close()
        def dlProgress(count, blockSize, totalSize):
            """Helper function to display dowload progress
            """
            percent = int(count*blockSize*100/totalSize)
            sys.stdout.write("\rDownloading " + \
                             file_name + \
                             "...%d%%" % percent)
            sys.stdout.flush()
        file_name = url.split('/')[-1]
        try:
            file_path = os.path.join(local, dest, file_name)
            if os.path.exists(file_path):
                print file_name + " already downloaded. Using it."
            else:
                privateDownload(url, file_path, reporthook=dlProgress)
                sys.stdout.write("\n")
            return file_path
        except IOError as e:
            print("Could not download " + file_name + ":" + str(e))

    def which(self, program):
        """ Check if a given executable is available from the path.
        """
        import sys
        if sys.platform == "win32" and not program.endswith(".exe"): program += ".exe"
        
        import os
        def is_exe(fpath):
            return os.path.isfile(fpath) and os.access(fpath, os.X_OK)

        fpath, fname = os.path.split(program)
        if fpath:
            if is_exe(program):
                return program
        else:
            for path in os.environ["PATH"].split(os.pathsep):
                exe_file = os.path.join(path, program)
                if is_exe(exe_file):
                    return exe_file

        return None
