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
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=linuxDebug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Application.o \
	${OBJECTDIR}/BspProp.o \
	${OBJECTDIR}/common/boundingbox.o \
	${OBJECTDIR}/fs/File.o \
	${OBJECTDIR}/fs/mesh/hlsdk/mathlib.o \
	${OBJECTDIR}/RenderOptions.o \
	${OBJECTDIR}/RenderMode.o \
	${OBJECTDIR}/BspGeometry.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/BspFace.o \
	${OBJECTDIR}/BspCollision.o \
	${OBJECTDIR}/BspEntity.o \
	${OBJECTDIR}/fs/FileSystemException.o \
	${OBJECTDIR}/fs/zip/mztools.o \
	${OBJECTDIR}/Console.o \
	${OBJECTDIR}/common/math3d.o \
	${OBJECTDIR}/common/camera.o \
	${OBJECTDIR}/common/vector3.o \
	${OBJECTDIR}/fs/image/png.o \
	${OBJECTDIR}/common/plane.o \
	${OBJECTDIR}/BspLeaf.o \
	${OBJECTDIR}/fs/image/bitmap.o \
	${OBJECTDIR}/fs/ZipPackage.o \
	${OBJECTDIR}/fs/FileSystem.o \
	${OBJECTDIR}/fs/zip/unzip.o \
	${OBJECTDIR}/fs/image/jpeg.o \
	${OBJECTDIR}/BspWorld.o \
	${OBJECTDIR}/SkyBox.o \
	${OBJECTDIR}/HlBspData.o \
	${OBJECTDIR}/fs/mesh/hlsdk/studio_render.o \
	${OBJECTDIR}/fs/image/targa.o \
	${OBJECTDIR}/fs/mesh/hlsdk/cmdlib.o \
	${OBJECTDIR}/BspNode.o \
	${OBJECTDIR}/fs/Resource.o \
	${OBJECTDIR}/BspLoader.o \
	${OBJECTDIR}/HlBspWorld.o \
	${OBJECTDIR}/fs/zip/zip.o \
	${OBJECTDIR}/Q3BspData.o \
	${OBJECTDIR}/fs/zip/ioapi.o \
	${OBJECTDIR}/TextureLoader.o \
	${OBJECTDIR}/Q3BspWorld.o \
	${OBJECTDIR}/fs/mesh/Mesh.o \
	${OBJECTDIR}/FreeTypeFont.o \
	${OBJECTDIR}/fs/image/texture.o \
	${OBJECTDIR}/common/thread.o \
	${OBJECTDIR}/fs/mesh/hlsdk/studio_utils.o \
	${OBJECTDIR}/common/tokenizer.o \
	${OBJECTDIR}/fs/mesh/Mdl.o \
	${OBJECTDIR}/common/common.o \
	${OBJECTDIR}/common/data.o \
	${OBJECTDIR}/fs/Package.o \
	${OBJECTDIR}/fs/WadPackage.o \
	${OBJECTDIR}/fs/image/miptex.o \
	${OBJECTDIR}/BspObject.o


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
LDLIBSOPTIONS=-lglfw -lGLU -lpthread -lXrandr -ljpeg -lpng -lfreetype -lz

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/learnbsp

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/learnbsp: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/learnbsp ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/Application.o: Application.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/freetype2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Application.o Application.cpp

${OBJECTDIR}/BspProp.o: BspProp.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/freetype2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/BspProp.o BspProp.cpp

${OBJECTDIR}/common/boundingbox.o: common/boundingbox.cpp 
	${MKDIR} -p ${OBJECTDIR}/common
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/freetype2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/common/boundingbox.o common/boundingbox.cpp

${OBJECTDIR}/fs/File.o: fs/File.cpp 
	${MKDIR} -p ${OBJECTDIR}/fs
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/freetype2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/fs/File.o fs/File.cpp

${OBJECTDIR}/fs/mesh/hlsdk/mathlib.o: fs/mesh/hlsdk/mathlib.c 
	${MKDIR} -p ${OBJECTDIR}/fs/mesh/hlsdk
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/fs/mesh/hlsdk/mathlib.o fs/mesh/hlsdk/mathlib.c

${OBJECTDIR}/RenderOptions.o: RenderOptions.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/freetype2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/RenderOptions.o RenderOptions.cpp

${OBJECTDIR}/RenderMode.o: RenderMode.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/freetype2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/RenderMode.o RenderMode.cpp

${OBJECTDIR}/BspGeometry.o: BspGeometry.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/freetype2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/BspGeometry.o BspGeometry.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/freetype2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/BspFace.o: BspFace.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/freetype2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/BspFace.o BspFace.cpp

${OBJECTDIR}/BspCollision.o: BspCollision.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/freetype2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/BspCollision.o BspCollision.cpp

${OBJECTDIR}/BspEntity.o: BspEntity.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/freetype2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/BspEntity.o BspEntity.cpp

${OBJECTDIR}/fs/FileSystemException.o: fs/FileSystemException.cpp 
	${MKDIR} -p ${OBJECTDIR}/fs
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/freetype2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/fs/FileSystemException.o fs/FileSystemException.cpp

${OBJECTDIR}/fs/zip/mztools.o: fs/zip/mztools.c 
	${MKDIR} -p ${OBJECTDIR}/fs/zip
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/fs/zip/mztools.o fs/zip/mztools.c

${OBJECTDIR}/Console.o: Console.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/freetype2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Console.o Console.cpp

${OBJECTDIR}/common/math3d.o: common/math3d.cpp 
	${MKDIR} -p ${OBJECTDIR}/common
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/freetype2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/common/math3d.o common/math3d.cpp

${OBJECTDIR}/common/camera.o: common/camera.cpp 
	${MKDIR} -p ${OBJECTDIR}/common
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/freetype2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/common/camera.o common/camera.cpp

${OBJECTDIR}/common/vector3.o: common/vector3.cpp 
	${MKDIR} -p ${OBJECTDIR}/common
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/freetype2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/common/vector3.o common/vector3.cpp

${OBJECTDIR}/fs/image/png.o: fs/image/png.cpp 
	${MKDIR} -p ${OBJECTDIR}/fs/image
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/freetype2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/fs/image/png.o fs/image/png.cpp

${OBJECTDIR}/common/plane.o: common/plane.cpp 
	${MKDIR} -p ${OBJECTDIR}/common
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/freetype2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/common/plane.o common/plane.cpp

${OBJECTDIR}/BspLeaf.o: BspLeaf.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/freetype2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/BspLeaf.o BspLeaf.cpp

${OBJECTDIR}/fs/image/bitmap.o: fs/image/bitmap.cpp 
	${MKDIR} -p ${OBJECTDIR}/fs/image
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/freetype2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/fs/image/bitmap.o fs/image/bitmap.cpp

${OBJECTDIR}/fs/ZipPackage.o: fs/ZipPackage.cpp 
	${MKDIR} -p ${OBJECTDIR}/fs
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/freetype2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/fs/ZipPackage.o fs/ZipPackage.cpp

${OBJECTDIR}/fs/FileSystem.o: fs/FileSystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/fs
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/freetype2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/fs/FileSystem.o fs/FileSystem.cpp

${OBJECTDIR}/fs/zip/unzip.o: fs/zip/unzip.c 
	${MKDIR} -p ${OBJECTDIR}/fs/zip
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/fs/zip/unzip.o fs/zip/unzip.c

${OBJECTDIR}/fs/image/jpeg.o: fs/image/jpeg.cpp 
	${MKDIR} -p ${OBJECTDIR}/fs/image
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/freetype2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/fs/image/jpeg.o fs/image/jpeg.cpp

${OBJECTDIR}/BspWorld.o: BspWorld.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/freetype2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/BspWorld.o BspWorld.cpp

${OBJECTDIR}/SkyBox.o: SkyBox.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/freetype2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/SkyBox.o SkyBox.cpp

${OBJECTDIR}/HlBspData.o: HlBspData.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/freetype2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/HlBspData.o HlBspData.cpp

${OBJECTDIR}/fs/mesh/hlsdk/studio_render.o: fs/mesh/hlsdk/studio_render.cpp 
	${MKDIR} -p ${OBJECTDIR}/fs/mesh/hlsdk
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/freetype2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/fs/mesh/hlsdk/studio_render.o fs/mesh/hlsdk/studio_render.cpp

${OBJECTDIR}/fs/image/targa.o: fs/image/targa.cpp 
	${MKDIR} -p ${OBJECTDIR}/fs/image
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/freetype2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/fs/image/targa.o fs/image/targa.cpp

${OBJECTDIR}/fs/mesh/hlsdk/cmdlib.o: fs/mesh/hlsdk/cmdlib.c 
	${MKDIR} -p ${OBJECTDIR}/fs/mesh/hlsdk
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/fs/mesh/hlsdk/cmdlib.o fs/mesh/hlsdk/cmdlib.c

${OBJECTDIR}/BspNode.o: BspNode.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/freetype2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/BspNode.o BspNode.cpp

${OBJECTDIR}/fs/Resource.o: fs/Resource.cpp 
	${MKDIR} -p ${OBJECTDIR}/fs
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/freetype2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/fs/Resource.o fs/Resource.cpp

${OBJECTDIR}/BspLoader.o: BspLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/freetype2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/BspLoader.o BspLoader.cpp

${OBJECTDIR}/HlBspWorld.o: HlBspWorld.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/freetype2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/HlBspWorld.o HlBspWorld.cpp

${OBJECTDIR}/fs/zip/zip.o: fs/zip/zip.c 
	${MKDIR} -p ${OBJECTDIR}/fs/zip
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/fs/zip/zip.o fs/zip/zip.c

${OBJECTDIR}/Q3BspData.o: Q3BspData.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/freetype2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Q3BspData.o Q3BspData.cpp

${OBJECTDIR}/fs/zip/ioapi.o: fs/zip/ioapi.c 
	${MKDIR} -p ${OBJECTDIR}/fs/zip
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/fs/zip/ioapi.o fs/zip/ioapi.c

${OBJECTDIR}/TextureLoader.o: TextureLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/freetype2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/TextureLoader.o TextureLoader.cpp

${OBJECTDIR}/Q3BspWorld.o: Q3BspWorld.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/freetype2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Q3BspWorld.o Q3BspWorld.cpp

${OBJECTDIR}/fs/mesh/Mesh.o: fs/mesh/Mesh.cpp 
	${MKDIR} -p ${OBJECTDIR}/fs/mesh
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/freetype2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/fs/mesh/Mesh.o fs/mesh/Mesh.cpp

${OBJECTDIR}/FreeTypeFont.o: FreeTypeFont.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/freetype2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/FreeTypeFont.o FreeTypeFont.cpp

${OBJECTDIR}/fs/image/texture.o: fs/image/texture.cpp 
	${MKDIR} -p ${OBJECTDIR}/fs/image
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/freetype2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/fs/image/texture.o fs/image/texture.cpp

${OBJECTDIR}/common/thread.o: common/thread.cpp 
	${MKDIR} -p ${OBJECTDIR}/common
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/freetype2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/common/thread.o common/thread.cpp

${OBJECTDIR}/fs/mesh/hlsdk/studio_utils.o: fs/mesh/hlsdk/studio_utils.cpp 
	${MKDIR} -p ${OBJECTDIR}/fs/mesh/hlsdk
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/freetype2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/fs/mesh/hlsdk/studio_utils.o fs/mesh/hlsdk/studio_utils.cpp

${OBJECTDIR}/common/tokenizer.o: common/tokenizer.cpp 
	${MKDIR} -p ${OBJECTDIR}/common
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/freetype2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/common/tokenizer.o common/tokenizer.cpp

${OBJECTDIR}/fs/mesh/Mdl.o: fs/mesh/Mdl.cpp 
	${MKDIR} -p ${OBJECTDIR}/fs/mesh
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/freetype2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/fs/mesh/Mdl.o fs/mesh/Mdl.cpp

${OBJECTDIR}/common/common.o: common/common.cpp 
	${MKDIR} -p ${OBJECTDIR}/common
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/freetype2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/common/common.o common/common.cpp

${OBJECTDIR}/common/data.o: common/data.cpp 
	${MKDIR} -p ${OBJECTDIR}/common
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/freetype2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/common/data.o common/data.cpp

${OBJECTDIR}/fs/Package.o: fs/Package.cpp 
	${MKDIR} -p ${OBJECTDIR}/fs
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/freetype2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/fs/Package.o fs/Package.cpp

${OBJECTDIR}/fs/WadPackage.o: fs/WadPackage.cpp 
	${MKDIR} -p ${OBJECTDIR}/fs
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/freetype2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/fs/WadPackage.o fs/WadPackage.cpp

${OBJECTDIR}/fs/image/miptex.o: fs/image/miptex.cpp 
	${MKDIR} -p ${OBJECTDIR}/fs/image
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/freetype2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/fs/image/miptex.o fs/image/miptex.cpp

${OBJECTDIR}/BspObject.o: BspObject.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/usr/include/freetype2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/BspObject.o BspObject.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/learnbsp

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
