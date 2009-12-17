#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=linuxRelease
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/common/font.o \
	${OBJECTDIR}/BspMesh.o \
	${OBJECTDIR}/BspFace.o \
	${OBJECTDIR}/fs/zip/zip.o \
	${OBJECTDIR}/common/boundingbox.o \
	${OBJECTDIR}/common/tokenizer.o \
	${OBJECTDIR}/common/stringfunctions.o \
	${OBJECTDIR}/fs/Package.o \
	${OBJECTDIR}/common/data.o \
	${OBJECTDIR}/common/renderoperations.o \
	${OBJECTDIR}/fs/image/miptex.o \
	${OBJECTDIR}/fs/File.o \
	${OBJECTDIR}/common/vector3.o \
	${OBJECTDIR}/Collision.o \
	${OBJECTDIR}/common/thread.o \
	${OBJECTDIR}/TextureLoader.o \
	${OBJECTDIR}/Application.o \
	${OBJECTDIR}/BspLeaf.o \
	${OBJECTDIR}/BspModel.o \
	${OBJECTDIR}/common/camera.o \
	${OBJECTDIR}/fs/image/bitmap.o \
	${OBJECTDIR}/BspObject.o \
	${OBJECTDIR}/BspData.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/common/texture.o \
	${OBJECTDIR}/fs/zip/ioapi.o \
	${OBJECTDIR}/fs/WadPackage.o \
	${OBJECTDIR}/fs/zip/mztools.o \
	${OBJECTDIR}/common/math3d.o \
	${OBJECTDIR}/fs/image/targa.o \
	${OBJECTDIR}/fs/FileSystem.o \
	${OBJECTDIR}/fs/ZipPackage.o \
	${OBJECTDIR}/BspWorld.o \
	${OBJECTDIR}/BspEntity.o \
	${OBJECTDIR}/fs/FileSystemException.o \
	${OBJECTDIR}/common/plane.o \
	${OBJECTDIR}/BspNode.o \
	${OBJECTDIR}/fs/zip/unzip.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-m32
CXXFLAGS=-m32

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lglfw -lGLU -lpthread -lXrandr lib/libz.a ../BspPlugin/dist/Release/GNU-Linux-x86/libbspplugin.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-linuxRelease.mk dist/linuxRelease/GNU-Linux-x86/learnbsp

dist/linuxRelease/GNU-Linux-x86/learnbsp: lib/libz.a

dist/linuxRelease/GNU-Linux-x86/learnbsp: ../BspPlugin/dist/Release/GNU-Linux-x86/libbspplugin.a

dist/linuxRelease/GNU-Linux-x86/learnbsp: ${OBJECTFILES}
	${MKDIR} -p dist/linuxRelease/GNU-Linux-x86
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/learnbsp ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/common/font.o: nbproject/Makefile-${CND_CONF}.mk common/font.cpp 
	${MKDIR} -p ${OBJECTDIR}/common
	$(COMPILE.cc) -O2 -I../BspPlugin -o ${OBJECTDIR}/common/font.o common/font.cpp

${OBJECTDIR}/BspMesh.o: nbproject/Makefile-${CND_CONF}.mk BspMesh.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -I../BspPlugin -o ${OBJECTDIR}/BspMesh.o BspMesh.cpp

${OBJECTDIR}/BspFace.o: nbproject/Makefile-${CND_CONF}.mk BspFace.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -I../BspPlugin -o ${OBJECTDIR}/BspFace.o BspFace.cpp

${OBJECTDIR}/fs/zip/zip.o: nbproject/Makefile-${CND_CONF}.mk fs/zip/zip.c 
	${MKDIR} -p ${OBJECTDIR}/fs/zip
	$(COMPILE.c) -O2 -o ${OBJECTDIR}/fs/zip/zip.o fs/zip/zip.c

${OBJECTDIR}/common/boundingbox.o: nbproject/Makefile-${CND_CONF}.mk common/boundingbox.cpp 
	${MKDIR} -p ${OBJECTDIR}/common
	$(COMPILE.cc) -O2 -I../BspPlugin -o ${OBJECTDIR}/common/boundingbox.o common/boundingbox.cpp

${OBJECTDIR}/common/tokenizer.o: nbproject/Makefile-${CND_CONF}.mk common/tokenizer.cpp 
	${MKDIR} -p ${OBJECTDIR}/common
	$(COMPILE.cc) -O2 -I../BspPlugin -o ${OBJECTDIR}/common/tokenizer.o common/tokenizer.cpp

${OBJECTDIR}/common/stringfunctions.o: nbproject/Makefile-${CND_CONF}.mk common/stringfunctions.cpp 
	${MKDIR} -p ${OBJECTDIR}/common
	$(COMPILE.cc) -O2 -I../BspPlugin -o ${OBJECTDIR}/common/stringfunctions.o common/stringfunctions.cpp

${OBJECTDIR}/fs/Package.o: nbproject/Makefile-${CND_CONF}.mk fs/Package.cpp 
	${MKDIR} -p ${OBJECTDIR}/fs
	$(COMPILE.cc) -O2 -I../BspPlugin -o ${OBJECTDIR}/fs/Package.o fs/Package.cpp

${OBJECTDIR}/common/data.o: nbproject/Makefile-${CND_CONF}.mk common/data.cpp 
	${MKDIR} -p ${OBJECTDIR}/common
	$(COMPILE.cc) -O2 -I../BspPlugin -o ${OBJECTDIR}/common/data.o common/data.cpp

${OBJECTDIR}/common/renderoperations.o: nbproject/Makefile-${CND_CONF}.mk common/renderoperations.cpp 
	${MKDIR} -p ${OBJECTDIR}/common
	$(COMPILE.cc) -O2 -I../BspPlugin -o ${OBJECTDIR}/common/renderoperations.o common/renderoperations.cpp

${OBJECTDIR}/fs/image/miptex.o: nbproject/Makefile-${CND_CONF}.mk fs/image/miptex.cpp 
	${MKDIR} -p ${OBJECTDIR}/fs/image
	$(COMPILE.cc) -O2 -I../BspPlugin -o ${OBJECTDIR}/fs/image/miptex.o fs/image/miptex.cpp

${OBJECTDIR}/fs/File.o: nbproject/Makefile-${CND_CONF}.mk fs/File.cpp 
	${MKDIR} -p ${OBJECTDIR}/fs
	$(COMPILE.cc) -O2 -I../BspPlugin -o ${OBJECTDIR}/fs/File.o fs/File.cpp

${OBJECTDIR}/common/vector3.o: nbproject/Makefile-${CND_CONF}.mk common/vector3.cpp 
	${MKDIR} -p ${OBJECTDIR}/common
	$(COMPILE.cc) -O2 -I../BspPlugin -o ${OBJECTDIR}/common/vector3.o common/vector3.cpp

${OBJECTDIR}/Collision.o: nbproject/Makefile-${CND_CONF}.mk Collision.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -I../BspPlugin -o ${OBJECTDIR}/Collision.o Collision.cpp

${OBJECTDIR}/common/thread.o: nbproject/Makefile-${CND_CONF}.mk common/thread.cpp 
	${MKDIR} -p ${OBJECTDIR}/common
	$(COMPILE.cc) -O2 -I../BspPlugin -o ${OBJECTDIR}/common/thread.o common/thread.cpp

${OBJECTDIR}/TextureLoader.o: nbproject/Makefile-${CND_CONF}.mk TextureLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -I../BspPlugin -o ${OBJECTDIR}/TextureLoader.o TextureLoader.cpp

${OBJECTDIR}/Application.o: nbproject/Makefile-${CND_CONF}.mk Application.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -I../BspPlugin -o ${OBJECTDIR}/Application.o Application.cpp

${OBJECTDIR}/BspLeaf.o: nbproject/Makefile-${CND_CONF}.mk BspLeaf.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -I../BspPlugin -o ${OBJECTDIR}/BspLeaf.o BspLeaf.cpp

${OBJECTDIR}/BspModel.o: nbproject/Makefile-${CND_CONF}.mk BspModel.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -I../BspPlugin -o ${OBJECTDIR}/BspModel.o BspModel.cpp

${OBJECTDIR}/common/camera.o: nbproject/Makefile-${CND_CONF}.mk common/camera.cpp 
	${MKDIR} -p ${OBJECTDIR}/common
	$(COMPILE.cc) -O2 -I../BspPlugin -o ${OBJECTDIR}/common/camera.o common/camera.cpp

${OBJECTDIR}/fs/image/bitmap.o: nbproject/Makefile-${CND_CONF}.mk fs/image/bitmap.cpp 
	${MKDIR} -p ${OBJECTDIR}/fs/image
	$(COMPILE.cc) -O2 -I../BspPlugin -o ${OBJECTDIR}/fs/image/bitmap.o fs/image/bitmap.cpp

${OBJECTDIR}/BspObject.o: nbproject/Makefile-${CND_CONF}.mk BspObject.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -I../BspPlugin -o ${OBJECTDIR}/BspObject.o BspObject.cpp

${OBJECTDIR}/BspData.o: nbproject/Makefile-${CND_CONF}.mk BspData.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -I../BspPlugin -o ${OBJECTDIR}/BspData.o BspData.cpp

${OBJECTDIR}/main.o: nbproject/Makefile-${CND_CONF}.mk main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -I../BspPlugin -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/common/texture.o: nbproject/Makefile-${CND_CONF}.mk common/texture.cpp 
	${MKDIR} -p ${OBJECTDIR}/common
	$(COMPILE.cc) -O2 -I../BspPlugin -o ${OBJECTDIR}/common/texture.o common/texture.cpp

${OBJECTDIR}/fs/zip/ioapi.o: nbproject/Makefile-${CND_CONF}.mk fs/zip/ioapi.c 
	${MKDIR} -p ${OBJECTDIR}/fs/zip
	$(COMPILE.c) -O2 -o ${OBJECTDIR}/fs/zip/ioapi.o fs/zip/ioapi.c

${OBJECTDIR}/fs/WadPackage.o: nbproject/Makefile-${CND_CONF}.mk fs/WadPackage.cpp 
	${MKDIR} -p ${OBJECTDIR}/fs
	$(COMPILE.cc) -O2 -I../BspPlugin -o ${OBJECTDIR}/fs/WadPackage.o fs/WadPackage.cpp

${OBJECTDIR}/fs/zip/mztools.o: nbproject/Makefile-${CND_CONF}.mk fs/zip/mztools.c 
	${MKDIR} -p ${OBJECTDIR}/fs/zip
	$(COMPILE.c) -O2 -o ${OBJECTDIR}/fs/zip/mztools.o fs/zip/mztools.c

${OBJECTDIR}/common/math3d.o: nbproject/Makefile-${CND_CONF}.mk common/math3d.cpp 
	${MKDIR} -p ${OBJECTDIR}/common
	$(COMPILE.cc) -O2 -I../BspPlugin -o ${OBJECTDIR}/common/math3d.o common/math3d.cpp

${OBJECTDIR}/fs/image/targa.o: nbproject/Makefile-${CND_CONF}.mk fs/image/targa.cpp 
	${MKDIR} -p ${OBJECTDIR}/fs/image
	$(COMPILE.cc) -O2 -I../BspPlugin -o ${OBJECTDIR}/fs/image/targa.o fs/image/targa.cpp

${OBJECTDIR}/fs/FileSystem.o: nbproject/Makefile-${CND_CONF}.mk fs/FileSystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/fs
	$(COMPILE.cc) -O2 -I../BspPlugin -o ${OBJECTDIR}/fs/FileSystem.o fs/FileSystem.cpp

${OBJECTDIR}/fs/ZipPackage.o: nbproject/Makefile-${CND_CONF}.mk fs/ZipPackage.cpp 
	${MKDIR} -p ${OBJECTDIR}/fs
	$(COMPILE.cc) -O2 -I../BspPlugin -o ${OBJECTDIR}/fs/ZipPackage.o fs/ZipPackage.cpp

${OBJECTDIR}/BspWorld.o: nbproject/Makefile-${CND_CONF}.mk BspWorld.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -I../BspPlugin -o ${OBJECTDIR}/BspWorld.o BspWorld.cpp

${OBJECTDIR}/BspEntity.o: nbproject/Makefile-${CND_CONF}.mk BspEntity.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -I../BspPlugin -o ${OBJECTDIR}/BspEntity.o BspEntity.cpp

${OBJECTDIR}/fs/FileSystemException.o: nbproject/Makefile-${CND_CONF}.mk fs/FileSystemException.cpp 
	${MKDIR} -p ${OBJECTDIR}/fs
	$(COMPILE.cc) -O2 -I../BspPlugin -o ${OBJECTDIR}/fs/FileSystemException.o fs/FileSystemException.cpp

${OBJECTDIR}/common/plane.o: nbproject/Makefile-${CND_CONF}.mk common/plane.cpp 
	${MKDIR} -p ${OBJECTDIR}/common
	$(COMPILE.cc) -O2 -I../BspPlugin -o ${OBJECTDIR}/common/plane.o common/plane.cpp

${OBJECTDIR}/BspNode.o: nbproject/Makefile-${CND_CONF}.mk BspNode.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -I../BspPlugin -o ${OBJECTDIR}/BspNode.o BspNode.cpp

${OBJECTDIR}/fs/zip/unzip.o: nbproject/Makefile-${CND_CONF}.mk fs/zip/unzip.c 
	${MKDIR} -p ${OBJECTDIR}/fs/zip
	$(COMPILE.c) -O2 -o ${OBJECTDIR}/fs/zip/unzip.o fs/zip/unzip.c

# Subprojects
.build-subprojects:
	cd ../BspPlugin && ${MAKE}  -f Makefile CONF=Release
	cd ../BspPlugin && ${MAKE}  -f Makefile CONF=Release
	cd ../Basics && ${MAKE}  -f Makefile CONF=Release
	cd ../BasicGame && ${MAKE}  -f Makefile CONF=Release

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/linuxRelease
	${RM} dist/linuxRelease/GNU-Linux-x86/learnbsp

# Subprojects
.clean-subprojects:
	cd ../BspPlugin && ${MAKE}  -f Makefile CONF=Release clean
	cd ../BspPlugin && ${MAKE}  -f Makefile CONF=Release clean
	cd ../Basics && ${MAKE}  -f Makefile CONF=Release clean
	cd ../BasicGame && ${MAKE}  -f Makefile CONF=Release clean
