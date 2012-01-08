import os
import sys

import urllib
import tarfile
import tempfile
import shutil
import subprocess
import glob
import platform; running_windows = True if platform.system == "Windows" else False

APP_NAME = "PhysicalEtoys"
APP_VERSION = "1.0"
PREFIX = "."

BOOTSTRAP_SCRIPT = "install_pe.st"

print("*** " + APP_NAME + " " + APP_VERSION + " bootstrapping ***\n")
r = raw_input("Do you want to use Richi special 'PE' base image (R) or the stock"
             " EToys image (E)? (default: R)\n")
if r in "eE":
    IMAGE_REPO = "http://download.sugarlabs.org/sources/sucrose/glucose/etoys/"
    IMAGE_VERSION = "etoys-4.1.2390"
else:
    IMAGE_REPO="http://dl.dropbox.com/u/43706148/pe_bootstrap/"
    IMAGE_VERSION="fresca.etoys.31"

print("Using image " + IMAGE_VERSION)
IMAGE_PATH = os.path.join(PREFIX, IMAGE_VERSION + ".tar.gz")


# Windows only
if running_windows:
    VM_REPO="http://dl.dropbox.com/u/43706148/pe_bootstrap/"
    VM_VERSION="VM.win32.1"
    VM_PATH = os.path.join(PREFIX, VM_VERSION + ".tar.gz")

APP_FULLNAME = APP_NAME + "-" + APP_VERSION
APP_PATH = os.path.join(PREFIX, APP_FULLNAME)

###############################################################################
def downloadto(file_name, remote, local = '.'):

	def dlProgress(count, blockSize, totalSize):
		"""Helper function to display dowload progress
		"""
		percent = int(count*blockSize*100/totalSize)
		sys.stdout.write("\rDownloading " + file_name + "...%d%%" % percent)
		sys.stdout.flush()
	
	url = remote + file_name
	try:
		urllib.urlretrieve(url, os.path.join(local, file_name), reporthook=dlProgress)
		sys.stdout.write("\n")
		
	except IOError as e:
		print("Could not download " + file_name + ":" + str(e))


if os.path.exists(APP_PATH):
	print("Attention: " + APP_PATH + " already exists!")
	r = raw_input("What should I do?\n'o':overwrite\n'c':cancel\n")
	if r != 'o':
		print("Cancelling.")
		sys.exit(1)

	#Delete previous version
	shutil.rmtree(APP_PATH)

if not os.path.exists(IMAGE_PATH):
	downloadto(IMAGE_VERSION + ".tar.gz", IMAGE_REPO, PREFIX)
else:
	print(IMAGE_VERSION + " already downloaded. Using it.")

if running_windows:
    if not os.path.exists(VM_PATH):
        downloadto(VM_VERSION + ".tar.gz", VM_REPO, PREFIX)
    else:
        print(VM_VERSION + " already downloaded. Using it.")

TMPDIR = tempfile.mkdtemp()
print("Created temporary directory " + TMPDIR)

print("Extracting " + IMAGE_VERSION + "...")
with tarfile.open(IMAGE_PATH) as tar:
	tar.extractall(TMPDIR)

print("Creating " + APP_PATH + " and copying relevant files")
shutil.move(os.path.join(TMPDIR, IMAGE_VERSION, 'Content'), APP_PATH)

if running_windows:
    print("Extracting VM...")
    tarfile.open(VM_PATH).extractall(APP_PATH)

print("Renaming image...")
for file in glob.glob(os.path.join(APP_PATH, "*.image")): #normally, only one file
    shutil.move(file, os.path.join(APP_PATH, APP_NAME + ".image"))
for file in glob.glob(os.path.join(APP_PATH, "*.changes")): #normally, only one file
    shutil.move(file, os.path.join(APP_PATH, APP_NAME + ".changes"))

# Delete tmp dir and all its content
print("Cleaning...")
shutil.rmtree(TMPDIR)
shutil.rmtree(os.path.join(APP_PATH, "ExampleEtoys"))
shutil.rmtree(os.path.join(APP_PATH, "fonts"))
for file in glob.glob(os.path.join(APP_PATH, "*.pr")):
    os.remove(file)


print("Bootstrapping the image. Wait for Squeak to close itself automatically.")

if running_windows:
    VM_EXEC = os.path.join(APP_PATH, "PhysicalEtoys")
else:
    VM_EXEC = "squeak"

subprocess.Popen([VM_EXEC, os.path.join(APP_PATH, APP_NAME + ".image"), os.path.join(os.getcwd(), BOOTSTRAP_SCRIPT)]).wait()

print("***** We are done! ******")
