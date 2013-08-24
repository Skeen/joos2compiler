import os, sys, subprocess
import string, random
import shutil
import urllib
import tarfile

Import(['env'])

# Configuration
BINUTILS_VERSION = "2.20"
GCC_VERSION      = "4.5.0"
GMP_VERSION      = "5.0.1"
MPFR_VERSION     = "2.4.2"
MPC_VERSION      = "0.8.1"
NEWLIB_VERSION   = "1.18.0"

TARGET           = "i586-elf"
PREFIX           = os.getcwd() + "/tools/"

tools_folder = 'tools/'
if not os.path.exists(tools_folder):
    os.makedirs(tools_folder)

# Configuration above
# Functions below

def MakeDir(target):
    if not os.path.exists(target):
        os.makedirs(target)

def Downloader(target):
    if not os.path.exists(target):
        urllib.urlretrieve(target)

def DownloaderToFolder(target, folder):
    saved_global_Path = os.getcwd()
    os.chdir(folder)
    Downloader(target)
    os.chdir(saved_global_Path)

def Unpacker(target):
    tarFile = tarfile.open(target)
    tarFile.extractall(target)

def UnpackerToFolder(target, folder):
    saved_global_Path = os.getcwd()
    os.chdir(folder)
    Unpacker(target)
    os.chdir(saved_global_Path)

def Download(target, source, env):
    # If target is not found, download it
    target_file   = str(target[0])
    if not os.path.exists(target_file):
        download_info_file = str(source[0])

        f = open(download_info_file)
        lines = f.readlines()
        f.close()
        
        download_file = lines[0]
        urllib.urlretrieve(download_file, target_file)
        #urllib.urlretrieve("ftp://" + download_file, target_file)

def Unpack(target, source, env):
    UnpackerToFolder(str(target[0]), tools_folder)

def NoOperation(target, source, env):
    # Do nothing
    return 0

# Binutils
download_binutils      = "#" + "conf/tools/binutils.txt"
tar_binutils           = "#" + "binutils-" + BINUTILS_VERSION + ".tar.gz"
env.Command(tar_binutils, download_binutils, Download)

# GCC_Core
download_gcc_core = "#" + "conf/tools/gcc_core.txt"
tar_gcc_core      = "#" + "gcc-core-" + GCC_VERSION + ".tar.gz"
env.Command(tar_gcc_core, download_gcc_core, Download)

# GCC_CXX
download_gcc_cxx = "#" + "conf/tools/gcc_cxx.txt"
tar_gcc_cxx      = "#" + "gcc-g++-" + GCC_VERSION + ".tar.gz"
env.Command(tar_gcc_cxx, download_gcc_cxx, Download)

# GMP
download_gmp = "#" + "conf/tools/gmp.txt"
tar_gmp      = "#" + "gmp-" + GMP_VERSION + ".tar.gz"
env.Command(tar_gmp, download_gmp, Download)

# MPFR
download_mpfr = "#" + "conf/tools/mpfr.txt"
tar_mpfr      = "#" + "mpfr-" + MPFR_VERSION + ".tar.gz"
env.Command(tar_mpfr, download_mpfr, Download)

# MPC
download_mpc = "#" + "conf/tools/mpc.txt"
tar_mpc      = "#" + "mpc-" + MPC_VERSION + ".tar.gz"
env.Command(tar_mpc, download_mpc, Download)

# Newlib
download_newlib = "#" + "conf/tools/newlib.txt"
tar_newlib      = "#" + "newlib-" + NEWLIB_VERSION + ".tar.gz"
env.Command(tar_newlib, download_newlib, Download)

# All Tools
get_tools = "get_tools"
env.jAlias("GetTools", get_tools, "Downloads and builds the nessicary tools")
env.Depends(get_tools, tar_binutils)
env.Depends(get_tools, tar_gcc_core)
env.Depends(get_tools, tar_gcc_cxx)
env.Depends(get_tools, tar_gmp)
env.Depends(get_tools, tar_mpfr)
env.Depends(get_tools, tar_mpc)
env.Depends(get_tools, tar_newlib)

env.Command(get_tools, [], NoOperation)
