import os
import sys

import urllib
import tarfile
import tempfile
import shutil
import subprocess

APP_NAME = "PhysicalEtoys"
APP_VERSION = "1.0"

BOOTSTRAP_SCRIPT = "test.st"

ETOYS_REPO = "http://download.sugarlabs.org/sources/sucrose/glucose/etoys/"
ETOYS_VERSION = "etoys-4.1.2390"

PREFIX = "."

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


APP_FULLNAME = APP_NAME + "-" + APP_VERSION
APP_PATH = os.path.join(PREFIX, APP_FULLNAME)
ETOYS_PATH= os.path.join(PREFIX, ETOYS_VERSION + ".tar.gz")

if os.path.exists(APP_PATH):
	print("Attention: " + APP_PATH + " already exists!")
	r = raw_input("What should I do?\n'o':overwrite\n'c':cancel\n")
	if r != 'o':
		print("Cancelling.")
		sys.exit(1)
	
	#Delete previous version
	shutil.rmtree(APP_PATH)

if not os.path.exists(ETOYS_PATH):
	downloadto(ETOYS_VERSION + ".tar.gz", ETOYS_REPO, PREFIX)
else:
	print("Image " + ETOYS_VERSION + " already downloaded. Using it.")

TMPDIR = tempfile.mkdtemp()
print("Created temporary directory " + TMPDIR)

print("Extracting " + ETOYS_VERSION + "...")
with tarfile.open(ETOYS_PATH) as tar:
	tar.extractall(TMPDIR)


print("Creating " + APP_PATH + " and copying relevant files")
shutil.move(os.path.join(TMPDIR, ETOYS_VERSION, 'Content'), APP_PATH)

print("Renaming image...")
shutil.move(os.path.join(APP_PATH, "etoys.image"),
			os.path.join(APP_PATH, APP_NAME + ".image"))
shutil.move(os.path.join(APP_PATH, "etoys.changes"),
			os.path.join(APP_PATH, APP_NAME + ".changes"))

# Delete tmp dir and all its content
shutil.rmtree(TMPDIR)

print("Bootstrapping the image. Close Squeak when it asks for.")

subprocess.Popen(["squeak", os.path.join(APP_PATH, APP_NAME + ".image"), os.path.join(os.getcwd(), BOOTSTRAP_SCRIPT)]).wait()

print("***** We are done! ******")
