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
CND_CONF=linuxDebug
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/fs/image/jpeg.o \
	${OBJECTDIR}/BspFace.o \
	${OBJECTDIR}/BspMesh.o \
	${OBJECTDIR}/common/boundingbox.o \
	${OBJECTDIR}/FreeTypeFont.o \
	${OBJECTDIR}/common/tokenizer.o \
	${OBJECTDIR}/fs/mesh/Mesh.o \
	${OBJECTDIR}/fs/Package.o \
	${OBJECTDIR}/common/data.o \
	${OBJECTDIR}/fs/File.o \
	${OBJECTDIR}/fs/image/miptex.o \
	${OBJECTDIR}/common/vector3.o \
	${OBJECTDIR}/TextureLoader.o \
	${OBJECTDIR}/common/common.o \
	${OBJECTDIR}/BspLeaf.o \
	${OBJECTDIR}/common/camera.o \
	${OBJECTDIR}/BspModel.o \
	${OBJECTDIR}/fs/image/bitmap.o \
	${OBJECTDIR}/BspObject.o \
	${OBJECTDIR}/common/texture.o \
	${OBJECTDIR}/RenderMode.o \
	${OBJECTDIR}/common/math3d.o \
	${OBJECTDIR}/fs/FileSystem.o \
	${OBJECTDIR}/Q3BspData.o \
	${OBJECTDIR}/common/plane.o \
	${OBJECTDIR}/BspNode.o \
	${OBJECTDIR}/fs/zip/unzip.o \
	${OBJECTDIR}/BspCollision.o \
	${OBJECTDIR}/fs/zip/zip.o \
	${OBJECTDIR}/Q3BspWorld.o \
	${OBJECTDIR}/common/thread.o \
	${OBJECTDIR}/Application.o \
	${OBJECTDIR}/BspLoader.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/RenderOptions.o \
	${OBJECTDIR}/HlBspWorld.o \
	${OBJECTDIR}/fs/zip/ioapi.o \
	${OBJECTDIR}/fs/WadPackage.o \
	${OBJECTDIR}/fs/image/png.o \
	${OBJECTDIR}/HlBspData.o \
	${OBJECTDIR}/fs/zip/mztools.o \
	${OBJECTDIR}/fs/image/targa.o \
	${OBJECTDIR}/BspProp.o \
	${OBJECTDIR}/fs/ZipPackage.o \
	${OBJECTDIR}/BspWorld.o \
	${OBJECTDIR}/fs/FileSystemException.o \
	${OBJECTDIR}/BspEntity.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lglfw -lGLU -lpthread -lXrandr lib/libz.a -ljpeg -lpng -lfreetype

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-linuxDebug.mk dist/linuxDebug/GNU-Linux-x86/learnbsp

dist/linuxDebug/GNU-Linux-x86/learnbsp: lib/libz.a

dist/linuxDebug/GNU-Linux-x86/learnbsp: ${OBJECTFILES}
	${MKDIR} -p dist/linuxDebug/GNU-Linux-x86
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/learnbsp ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/fs/image/jpeg.o: nbproject/Makefile-${CND_CONF}.mk fs/image/jpeg.cpp 
	${MKDIR} -p ${OBJECTDIR}/fs/image
	$(COMPILE.cc) -g -I/usr/include/freetype2 -o ${OBJECTDIR}/fs/image/jpeg.o fs/image/jpeg.cpp

${OBJECTDIR}/BspFace.o: nbproject/Makefile-${CND_CONF}.mk BspFace.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -I/usr/include/freetype2 -o ${OBJECTDIR}/BspFace.o BspFace.cpp

${OBJECTDIR}/BspMesh.o: nbproject/Makefile-${CND_CONF}.mk BspMesh.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -I/usr/include/freetype2 -o ${OBJECTDIR}/BspMesh.o BspMesh.cpp

${OBJECTDIR}/common/boundingbox.o: nbproject/Makefile-${CND_CONF}.mk common/boundingbox.cpp 
	${MKDIR} -p ${OBJECTDIR}/common
	$(COMPILE.cc) -g -I/usr/include/freetype2 -o ${OBJECTDIR}/common/boundingbox.o common/boundingbox.cpp

${OBJECTDIR}/FreeTypeFont.o: nbproject/Makefile-${CND_CONF}.mk FreeTypeFont.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -I/usr/include/freetype2 -o ${OBJECTDIR}/FreeTypeFont.o FreeTypeFont.cpp

${OBJECTDIR}/common/tokenizer.o: nbproject/Makefile-${CND_CONF}.mk common/tokenizer.cpp 
	${MKDIR} -p ${OBJECTDIR}/common
	$(COMPILE.cc) -g -I/usr/include/freetype2 -o ${OBJECTDIR}/common/tokenizer.o common/tokenizer.cpp

${OBJECTDIR}/fs/mesh/Mesh.o: nbproject/Makefile-${CND_CONF}.mk fs/mesh/Mesh.cpp 
	${MKDIR} -p ${OBJECTDIR}/fs/mesh
	$(COMPILE.cc) -g -I/usr/include/freetype2 -o ${OBJECTDIR}/fs/mesh/Mesh.o fs/mesh/Mesh.cpp

${OBJECTDIR}/fs/Package.o: nbproject/Makefile-${CND_CONF}.mk fs/Package.cpp 
	${MKDIR} -p ${OBJECTDIR}/fs
	$(COMPILE.cc) -g -I/usr/include/freetype2 -o ${OBJECTDIR}/fs/Package.o fs/Package.cpp

${OBJECTDIR}/common/data.o: nbproject/Makefile-${CND_CONF}.mk common/data.cpp 
	${MKDIR} -p ${OBJECTDIR}/common
	$(COMPILE.cc) -g -I/usr/include/freetype2 -o ${OBJECTDIR}/common/data.o common/data.cpp

${OBJECTDIR}/fs/File.o: nbproject/Makefile-${CND_CONF}.mk fs/File.cpp 
	${MKDIR} -p ${OBJECTDIR}/fs
	$(COMPILE.cc) -g -I/usr/include/freetype2 -o ${OBJECTDIR}/fs/File.o fs/File.cpp

${OBJECTDIR}/fs/image/miptex.o: nbproject/Makefile-${CND_CONF}.mk fs/image/miptex.cpp 
	${MKDIR} -p ${OBJECTDIR}/fs/image
	$(COMPILE.cc) -g -I/usr/include/freetype2 -o ${OBJECTDIR}/fs/image/miptex.o fs/image/miptex.cpp

${OBJECTDIR}/common/vector3.o: nbproject/Makefile-${CND_CONF}.mk common/vector3.cpp 
	${MKDIR} -p ${OBJECTDIR}/common
	$(COMPILE.cc) -g -I/usr/include/freetype2 -o ${OBJECTDIR}/common/vector3.o common/vector3.cpp

${OBJECTDIR}/TextureLoader.o: nbproject/Makefile-${CND_CONF}.mk TextureLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -I/usr/include/freetype2 -o ${OBJECTDIR}/TextureLoader.o TextureLoader.cpp

${OBJECTDIR}/common/common.o: nbproject/Makefile-${CND_CONF}.mk common/common.cpp 
	${MKDIR} -p ${OBJECTDIR}/common
	$(COMPILE.cc) -g -I/usr/include/freetype2 -o ${OBJECTDIR}/common/common.o common/common.cpp

${OBJECTDIR}/BspLeaf.o: nbproject/Makefile-${CND_CONF}.mk BspLeaf.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -I/usr/include/freetype2 -o ${OBJECTDIR}/BspLeaf.o BspLeaf.cpp

${OBJECTDIR}/common/camera.o: nbproject/Makefile-${CND_CONF}.mk common/camera.cpp 
	${MKDIR} -p ${OBJECTDIR}/common
	$(COMPILE.cc) -g -I/usr/include/freetype2 -o ${OBJECTDIR}/common/camera.o common/camera.cpp

${OBJECTDIR}/BspModel.o: nbproject/Makefile-${CND_CONF}.mk BspModel.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -I/usr/include/freetype2 -o ${OBJECTDIR}/BspModel.o BspModel.cpp

${OBJECTDIR}/fs/image/bitmap.o: nbproject/Makefile-${CND_CONF}.mk fs/image/bitmap.cpp 
	${MKDIR} -p ${OBJECTDIR}/fs/image
	$(COMPILE.cc) -g -I/usr/include/freetype2 -o ${OBJECTDIR}/fs/image/bitmap.o fs/image/bitmap.cpp

${OBJECTDIR}/BspObject.o: nbproject/Makefile-${CND_CONF}.mk BspObject.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -I/usr/include/freetype2 -o ${OBJECTDIR}/BspObject.o BspObject.cpp

${OBJECTDIR}/common/texture.o: nbproject/Makefile-${CND_CONF}.mk common/texture.cpp 
	${MKDIR} -p ${OBJECTDIR}/common
	$(COMPILE.cc) -g -I/usr/include/freetype2 -o ${OBJECTDIR}/common/texture.o common/texture.cpp

${OBJECTDIR}/RenderMode.o: nbproject/Makefile-${CND_CONF}.mk RenderMode.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -I/usr/include/freetype2 -o ${OBJECTDIR}/RenderMode.o RenderMode.cpp

${OBJECTDIR}/common/math3d.o: nbproject/Makefile-${CND_CONF}.mk common/math3d.cpp 
	${MKDIR} -p ${OBJECTDIR}/common
	$(COMPILE.cc) -g -I/usr/include/freetype2 -o ${OBJECTDIR}/common/math3d.o common/math3d.cpp

${OBJECTDIR}/fs/FileSystem.o: nbproject/Makefile-${CND_CONF}.mk fs/FileSystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/fs
	$(COMPILE.cc) -g -I/usr/include/freetype2 -o ${OBJECTDIR}/fs/FileSystem.o fs/FileSystem.cpp

${OBJECTDIR}/Q3BspData.o: nbproject/Makefile-${CND_CONF}.mk Q3BspData.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -I/usr/include/freetype2 -o ${OBJECTDIR}/Q3BspData.o Q3BspData.cpp

${OBJECTDIR}/common/plane.o: nbproject/Makefile-${CND_CONF}.mk common/plane.cpp 
	${MKDIR} -p ${OBJECTDIR}/common
	$(COMPILE.cc) -g -I/usr/include/freetype2 -o ${OBJECTDIR}/common/plane.o common/plane.cpp

${OBJECTDIR}/BspNode.o: nbproject/Makefile-${CND_CONF}.mk BspNode.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -I/usr/include/freetype2 -o ${OBJECTDIR}/BspNode.o BspNode.cpp

${OBJECTDIR}/fs/zip/unzip.o: nbproject/Makefile-${CND_CONF}.mk fs/zip/unzip.c 
	${MKDIR} -p ${OBJECTDIR}/fs/zip
	$(COMPILE.c) -g -o ${OBJECTDIR}/fs/zip/unzip.o fs/zip/unzip.c

${OBJECTDIR}/BspCollision.o: nbproject/Makefile-${CND_CONF}.mk BspCollision.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -I/usr/include/freetype2 -o ${OBJECTDIR}/BspCollision.o BspCollision.cpp

${OBJECTDIR}/fs/zip/zip.o: nbproject/Makefile-${CND_CONF}.mk fs/zip/zip.c 
	${MKDIR} -p ${OBJECTDIR}/fs/zip
	$(COMPILE.c) -g -o ${OBJECTDIR}/fs/zip/zip.o fs/zip/zip.c

${OBJECTDIR}/Q3BspWorld.o: nbproject/Makefile-${CND_CONF}.mk Q3BspWorld.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -I/usr/include/freetype2 -o ${OBJECTDIR}/Q3BspWorld.o Q3BspWorld.cpp

${OBJECTDIR}/common/thread.o: nbproject/Makefile-${CND_CONF}.mk common/thread.cpp 
	${MKDIR} -p ${OBJECTDIR}/common
	$(COMPILE.cc) -g -I/usr/include/freetype2 -o ${OBJECTDIR}/common/thread.o common/thread.cpp

${OBJECTDIR}/Application.o: nbproject/Makefile-${CND_CONF}.mk Application.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -I/usr/include/freetype2 -o ${OBJECTDIR}/Application.o Application.cpp

${OBJECTDIR}/BspLoader.o: nbproject/Makefile-${CND_CONF}.mk BspLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -I/usr/include/freetype2 -o ${OBJECTDIR}/BspLoader.o BspLoader.cpp

${OBJECTDIR}/main.o: nbproject/Makefile-${CND_CONF}.mk main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -I/usr/include/freetype2 -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/RenderOptions.o: nbproject/Makefile-${CND_CONF}.mk RenderOptions.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -I/usr/include/freetype2 -o ${OBJECTDIR}/RenderOptions.o RenderOptions.cpp

${OBJECTDIR}/HlBspWorld.o: nbproject/Makefile-${CND_CONF}.mk HlBspWorld.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -I/usr/include/freetype2 -o ${OBJECTDIR}/HlBspWorld.o HlBspWorld.cpp

${OBJECTDIR}/fs/zip/ioapi.o: nbproject/Makefile-${CND_CONF}.mk fs/zip/ioapi.c 
	${MKDIR} -p ${OBJECTDIR}/fs/zip
	$(COMPILE.c) -g -o ${OBJECTDIR}/fs/zip/ioapi.o fs/zip/ioapi.c

${OBJECTDIR}/fs/WadPackage.o: nbproject/Makefile-${CND_CONF}.mk fs/WadPackage.cpp 
	${MKDIR} -p ${OBJECTDIR}/fs
	$(COMPILE.cc) -g -I/usr/include/freetype2 -o ${OBJECTDIR}/fs/WadPackage.o fs/WadPackage.cpp

${OBJECTDIR}/fs/image/png.o: nbproject/Makefile-${CND_CONF}.mk fs/image/png.cpp 
	${MKDIR} -p ${OBJECTDIR}/fs/image
	$(COMPILE.cc) -g -I/usr/include/freetype2 -o ${OBJECTDIR}/fs/image/png.o fs/image/png.cpp

${OBJECTDIR}/HlBspData.o: nbproject/Makefile-${CND_CONF}.mk HlBspData.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -I/usr/include/freetype2 -o ${OBJECTDIR}/HlBspData.o HlBspData.cpp

${OBJECTDIR}/fs/zip/mztools.o: nbproject/Makefile-${CND_CONF}.mk fs/zip/mztools.c 
	${MKDIR} -p ${OBJECTDIR}/fs/zip
	$(COMPILE.c) -g -o ${OBJECTDIR}/fs/zip/mztools.o fs/zip/mztools.c

${OBJECTDIR}/fs/image/targa.o: nbproject/Makefile-${CND_CONF}.mk fs/image/targa.cpp 
	${MKDIR} -p ${OBJECTDIR}/fs/image
	$(COMPILE.cc) -g -I/usr/include/freetype2 -o ${OBJECTDIR}/fs/image/targa.o fs/image/targa.cpp

${OBJECTDIR}/BspProp.o: nbproject/Makefile-${CND_CONF}.mk BspProp.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -I/usr/include/freetype2 -o ${OBJECTDIR}/BspProp.o BspProp.cpp

${OBJECTDIR}/fs/ZipPackage.o: nbproject/Makefile-${CND_CONF}.mk fs/ZipPackage.cpp 
	${MKDIR} -p ${OBJECTDIR}/fs
	$(COMPILE.cc) -g -I/usr/include/freetype2 -o ${OBJECTDIR}/fs/ZipPackage.o fs/ZipPackage.cpp

${OBJECTDIR}/BspWorld.o: nbproject/Makefile-${CND_CONF}.mk BspWorld.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -I/usr/include/freetype2 -o ${OBJECTDIR}/BspWorld.o BspWorld.cpp

${OBJECTDIR}/fs/FileSystemException.o: nbproject/Makefile-${CND_CONF}.mk fs/FileSystemException.cpp 
	${MKDIR} -p ${OBJECTDIR}/fs
	$(COMPILE.cc) -g -I/usr/include/freetype2 -o ${OBJECTDIR}/fs/FileSystemException.o fs/FileSystemException.cpp

${OBJECTDIR}/BspEntity.o: nbproject/Makefile-${CND_CONF}.mk BspEntity.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -I/usr/include/freetype2 -o ${OBJECTDIR}/BspEntity.o BspEntity.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/linuxDebug
	${RM} dist/linuxDebug/GNU-Linux-x86/learnbsp

# Subprojects
.clean-subprojects:
