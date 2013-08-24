import os, sys, subprocess
import string, random
import shutil
import urllib
import tarfile
import zipfile
from zipfile import ZipFile
            
Import(['env'])

objname = 'get-tools'
env.jAlias("tools", objname, "Get the project tools")

tools_folder = 'tools/'
libs_folder = 'libs/'

gcc_version = 'gcc-4.7.2'
gcc_tar = gcc_version + ".tar.gz"
binutils_version = 'binutils-2.23'
binutils_tar = binutils_version + ".tar.gz"

def prepareLibs():
    if not os.path.exists(libs_folder):
        os.makedirs(libs_folder)   

def prepareTools():
    # Let's make a working folder
    if not os.path.exists(tools_folder):
        os.makedirs(tools_folder)

def downloadGCC():
    if not os.path.exists(binutils_tar):
        print("Downloading binutils source")
        # Lets download our binutils stuff
        urllib.urlretrieve("http://ftp.gnu.org/gnu/binutils/" + binutils_tar, binutils_tar)
        
    if not os.path.exists(gcc_tar):
        print("Downloading GCC source")
        # Lets download our GCC stuff
        urllib.urlretrieve("http://ftp.gnu.org/gnu/gcc/" + gcc_version + "/" + gcc_tar, gcc_tar)

def unpackGCC():
    if not os.path.exists(binutils_version):
        print("Unpacking binutils source")
        # Lets unpack our binutils stuff            
        tarFile = tarfile.open(binutils_tar)
        tarFile.extractall(binutils_version)
        #os.system("tar -xvzf " + binutils_tar)
    if not os.path.exists(gcc_version):
        print("Unpacking GCC source")
        # Lets unpack our GCC stuff
        tarFile = tarfile.open(gcc_tar)
        tarFile.extractall(gcc_version)
        #os.system("tar -xvzf " + gcc_tar)

def buildGCC():
    # Setup our exports
    os.environ["PREFIX"] = os.getcwd() + "/crossgcc/"
    os.environ["TARGET"] = "i586-elf"

    # Setup build folders
    build_binutils = 'build-binutils/'
    build_gcc = 'build-gcc/'
    
    if not os.path.exists(build_binutils):
        os.makedirs(build_binutils)
    if not os.path.exists(build_gcc):
        os.makedirs(build_gcc)

    # Save our build root folder
    saved_global_Path = os.getcwd()
    
    # Build binutils
    print("Building binutils")
    os.chdir(build_binutils)
    os.system("../" + binutils_version + "/configure --target=$TARGET --prefix=$PREFIX --disable-nls")
    os.system("make all")
    os.system("make install")
    
    # Build GCC
    print("Building gcc")
    os.chdir(saved_global_Path)
    os.chdir(build_gcc)
    os.environ["PATH"] = os.environ["PATH"] + ":" + os.environ["PATH"] + "/bin"
    os.system("../" + gcc_version + "/configure --target=$TARGET --prefix=$PREFIX --disable-nls --enable-languages=c,c++ --without-headers")
    os.system("make all-gcc")
    os.system("make install-gcc")

    # Restore workdir
    os.chdir(saved_global_Path)

# Assuming everything went alright, we'll just get rid of whatever stuff we downloaded.
def cleanupGCC():
    os.remove(gcc_tar)
    shutil.rmtree(gcc_version, ignore_errors=True)
    shutil.rmtree(build_gcc, ignore_errors=True)

    os.remove(binutils_tar)
    shutil.rmtree(binutils_version, ignore_errors=True)   
    shutil.rmtree(build_binutils, ignore_errors=True)

def getGCC():
    if os.path.exists(tools_folder + "/crossgcc/"):
        return
    
    print("------------------------")
    print("GETTING GCC and BINUTILS")
    print("------------------------")
    
    # Now let's change to this new directory
    saved_global_Path = os.getcwd()
    os.chdir(tools_folder)

    # Do what needs to be done
    # Download the tar achives
    downloadGCC()
    # Unpack the tar archives
    unpackGCC()
    # Build the compiler
    buildGCC()
    # Clean up everything
    cleanupGCC()

    # And restore the working directory
    os.chdir(saved_global_Path)

# Downloads the mkisofs util, such that it is placed within the tools folder.
# Also this util should clean up itself properly when sucessfull.
# TODO: Currently lacking an implementation for UNIX.
def getMkisofs():
    if os.path.exists(tools_folder + "/mkisofs"):
        return

    
    print("---------------")
    print("GETTING mkisofs")
    print("---------------")

    # Now let's change to this new directory
    saved_global_Path = os.getcwd()
    os.chdir(tools_folder)
    
    if sys.platform == 'cygwin':
        mkisofs_version = "genisoimage-1.1.7.1-1"
        mkisofs_tar = mkisofs_version + ".tar.bz2"
    
        if not os.path.exists(mkisofs_tar):
            print("Downloading mkisofs program")
            # Lets download our mkisofs stuff
            urllib.urlretrieve("http://mirror.nyi.net/cygwin/release/cdrkit/genisoimage/" + mkisofs_tar, mkisofs_tar)
        if not os.path.exists(mkisofs_version):
            print("Unpacking mkisofs program")
            # Lets unpack our mkisofs stuff
            tarFile = tarfile.open(mkisofs_tar)
            tarFile.extractall(mkisofs_version)

        print("Preparing mkisofs program")
        # Now lets move mkisofs out of there.
        shutil.copyfile(mkisofs_version + "/usr/bin/genisoimage.exe", "mkisofs.exe")
        os.system("chmod +x mkisofs.exe")

        # Clean up
        os.remove(mkisofs_tar)
        shutil.rmtree(mkisofs_version, ignore_errors=True)
        
    else:
        print("Please provide a mkisofs program to tools/mkisofs (binary)")

    # And restore the working directory
    os.chdir(saved_global_Path)

# Downloads the QEMU util, such that it is placed within the tools folder.
# Also this util should clean up itself properly when sucessfull.
# TODO: Currently lacking an implementation for UNIX.
def getQEMU():
    if os.path.exists(tools_folder + "/QEMU/"):
        return

    print("------------")
    print("GETTING QEMU")
    print("------------")

    # Now let's change to this new directory
    saved_global_Path = os.getcwd()
    os.chdir(tools_folder)

    if sys.platform == 'cygwin':
        qemu_version = "Qemu-1.3.0-windows"
        qemu_tar = qemu_version + ".tar"

        if not os.path.exists(qemu_tar):
            print("Downloading qemu program")
            # Lets download our qemu stuff
            urllib.urlretrieve("http://cs.au.dk/~skeen/qemu/" + qemu_tar, qemu_tar)
        if not os.path.exists(qemu_version):
            print("Unpacking qemu program")
            # Lets unpack our qemu stuff
            tarFile = tarfile.open(qemu_tar)
            tarFile.extractall(".")

        print("Preparing qemu program")
        os.system("chmod +x QEMU/qemu-system-i386w.exe")
        os.remove(qemu_tar)
    else:
        print("Please provide a QEMU program to tools/QEMU/qemu-system-i386w.exe (binary)")
        
    # And restore the working directory
    os.chdir(saved_global_Path)

newlib_version = "newlib-1.19.0"
newlib_tar = newlib_version + ".tar.gz"

def downloadNewLib():
    if os.path.exists(newlib_version):
        return
    
    if sys.platform == 'cygwin':
        if not os.path.exists(newlib_tar):
            print("Downloading newlib source")
            # Lets download our qemu stuff
            urllib.urlretrieve("ftp://sources.redhat.com/pub/newlib/" + newlib_tar, newlib_tar)
        if not os.path.exists(newlib_version):
            print("Unpacking newlib source")
            # Lets unpack our qemu stuff
            tarFile = tarfile.open(newlib_tar)
            tarFile.extractall(".")

        os.remove(newlib_tar)
    else:
        print("Please provide a newlib source tree program to tools/" + newlib_version + "/ (folder)")

def buildNewLib():
    os.environ["PREFIX"] = os.getcwd() + "/newlib/"
    os.environ["TARGET"] = "i586-elf"
    os.environ["PATH"] = os.environ["PATH"] + ":" + os.getcwd() + "/crossgcc/bin"
    
    # Setup build folders
    build_newlib = 'build-newlib/'
    
    if not os.path.exists(build_newlib):
        os.makedirs(build_newlib)

    # Save our build root folder
    saved_global_Path = os.getcwd()
    
    # Build newlib
    print("Building newlib")
    os.chdir(build_newlib)
    os.system("../" + newlib_version + "/configure --target=$TARGET --prefix=$PREFIX")
    os.system("make all install")

def cleanupNewLib():
    shutil.rmtree(newlib_version, ignore_errors=True)
    shutil.rmtree(build_newlib, ignore_errors=True)

def moveNewLib():
    shutil.copytree("newlib/i586-elf/", "../" + libs_folder + "/newlib")

def getNewLib():
    if os.path.exists(tools_folder + "/newlib/"):
        return

    print("--------------")
    print("GETTING newlib")
    print("--------------")
    
    # Now let's change to this new directory
    saved_global_Path = os.getcwd()
    os.chdir(tools_folder)

    # Do what needs to be done
    # Download the tar achives
    # (and unpack)
    downloadNewLib()
    # Build the lib
    buildNewLib()
    # Clean up
    cleanupNewLib()
    # Move to the external libs folder
    moveNewLib()

    # And restore the working directory
    os.chdir(saved_global_Path)

def downloadLibSupCXX():
    # Same as GCC source
    if not os.path.exists(gcc_tar):
        print("Downloading LibSupCXX source")
        # Lets download our GCC stuff
        urllib.urlretrieve("http://ftp.gnu.org/gnu/gcc/" + gcc_version + "/" + gcc_tar, gcc_tar)

def unpackLibSupCXX():
    # Same as GCC source
    if not os.path.exists(gcc_version):
        print("Unpacking GCC source")
        # Lets unpack our GCC stuff
        tarFile = tarfile.open(gcc_tar)
        tarFile.extractall(gcc_version)

def buildLibSupCXX():
    # Setup our exports
    os.environ["PREFIX"] = os.getcwd() + "/LibSupCXX/"
    os.environ["TARGET"] = "i586-elf"

    # Setup build folders
    build_gcc = 'build-gcc/'
    build_LibSupCXX = 'build-LibSupCXX/'

    if not os.path.exists(build_gcc):
        os.makedirs(build_gcc)
    if not os.path.exists(build_LibSupCXX):
        os.makedirs(build_LibSupCXX)

    # Save our build root folder
    saved_global_Path = os.getcwd()

    # Configure GCC
#    print("Configure GCC")
#    os.chdir(build_gcc)
#    os.system("../" + gcc_version + "/configure --target=$TARGET --prefix=$PREFIX --disable-nls --enable-languages=c,c++ --without-headers")
    # Make LibSupCXX
    print("Build LibSupCXX")
    os.chdir(saved_global_Path)
    os.chdir(build_LibSupCXX)
    #os.chdir("libstdc++-v3")


    os.environ["PATH"] = os.environ["PATH"] + ":" + os.environ["PATH"] + "../../crossgcc/bin/"

    os.system("../" + gcc_version + "/libstdc++-v3/configure --target=$TARGET --prefix=$PREFIX --disable-nls")
    
   # + " ./configure --host=$TARGET --prefix=$PREFIX --disable-hosted-libstdcxx --disable-nls"

    os.chdir("include")
    os.system("make")
    os.system("make install")

    os.chdir("../libsupc++")
    os.system("make")
    os.system("make install")

def getLibSupCXX():

    if os.path.exists(tools_folder + "/LibSupCXX/"):
        return
    
    print("------------------")
    print("GETTING LibSuppCXX")
    print("------------------")
    
    # Now let's change to this new directory
    saved_global_Path = os.getcwd()
    os.chdir(tools_folder)

    #downloadLibSupCXX()
    #unpackLibSupCXX()
    # Build
    buildLibSupCXX()

def getTools(target, source, env):
    prepareTools()
    prepareLibs()
    getGCC()
    getMkisofs()
    getQEMU()
    getNewLib()

    #getLibSupCXX()

env.Command(objname, [], Action(getTools, None))

