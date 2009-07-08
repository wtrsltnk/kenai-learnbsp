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
CC=gcc.exe
CCC=g++.exe
CXX=g++.exe
FC=
AS=as.exe

# Macros
CND_PLATFORM=MinGW-Windows
CND_CONF=win32Release
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Application.o \
	${OBJECTDIR}/common/font.o \
	${OBJECTDIR}/BspFace.o \
	${OBJECTDIR}/BspLeaf.o \
	${OBJECTDIR}/BspModel.o \
	${OBJECTDIR}/common/camera.o \
	${OBJECTDIR}/BspObject.o \
	${OBJECTDIR}/BspData.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/common/texture.o \
	${OBJECTDIR}/GLee/GLee.o \
	${OBJECTDIR}/common/math3d.o \
	${OBJECTDIR}/BspWorld.o \
	${OBJECTDIR}/common/data.o \
	${OBJECTDIR}/common/plane.o \
	${OBJECTDIR}/common/vector3.o \
	${OBJECTDIR}/BspNode.o \
	${OBJECTDIR}/TextureLoader.o

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
LDLIBSOPTIONS=-lglfw -lopengl32 -lglu32

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-win32Release.mk dist/win32Release/MinGW-Windows/learnbsp.exe

dist/win32Release/MinGW-Windows/learnbsp.exe: ${OBJECTFILES}
	${MKDIR} -p dist/win32Release/MinGW-Windows
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/learnbsp ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/Application.o: nbproject/Makefile-${CND_CONF}.mk Application.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Application.o Application.cpp

${OBJECTDIR}/common/font.o: nbproject/Makefile-${CND_CONF}.mk common/font.cpp 
	${MKDIR} -p ${OBJECTDIR}/common
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/common/font.o common/font.cpp

${OBJECTDIR}/BspFace.o: nbproject/Makefile-${CND_CONF}.mk BspFace.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/BspFace.o BspFace.cpp

${OBJECTDIR}/BspLeaf.o: nbproject/Makefile-${CND_CONF}.mk BspLeaf.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/BspLeaf.o BspLeaf.cpp

${OBJECTDIR}/BspModel.o: nbproject/Makefile-${CND_CONF}.mk BspModel.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/BspModel.o BspModel.cpp

${OBJECTDIR}/common/camera.o: nbproject/Makefile-${CND_CONF}.mk common/camera.cpp 
	${MKDIR} -p ${OBJECTDIR}/common
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/common/camera.o common/camera.cpp

${OBJECTDIR}/BspObject.o: nbproject/Makefile-${CND_CONF}.mk BspObject.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/BspObject.o BspObject.cpp

${OBJECTDIR}/BspData.o: nbproject/Makefile-${CND_CONF}.mk BspData.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/BspData.o BspData.cpp

${OBJECTDIR}/main.o: nbproject/Makefile-${CND_CONF}.mk main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/common/texture.o: nbproject/Makefile-${CND_CONF}.mk common/texture.cpp 
	${MKDIR} -p ${OBJECTDIR}/common
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/common/texture.o common/texture.cpp

${OBJECTDIR}/GLee/GLee.o: nbproject/Makefile-${CND_CONF}.mk GLee/GLee.c 
	${MKDIR} -p ${OBJECTDIR}/GLee
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/GLee/GLee.o GLee/GLee.c

${OBJECTDIR}/common/math3d.o: nbproject/Makefile-${CND_CONF}.mk common/math3d.cpp 
	${MKDIR} -p ${OBJECTDIR}/common
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/common/math3d.o common/math3d.cpp

${OBJECTDIR}/BspWorld.o: nbproject/Makefile-${CND_CONF}.mk BspWorld.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/BspWorld.o BspWorld.cpp

${OBJECTDIR}/common/data.o: nbproject/Makefile-${CND_CONF}.mk common/data.cpp 
	${MKDIR} -p ${OBJECTDIR}/common
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/common/data.o common/data.cpp

${OBJECTDIR}/common/plane.o: nbproject/Makefile-${CND_CONF}.mk common/plane.cpp 
	${MKDIR} -p ${OBJECTDIR}/common
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/common/plane.o common/plane.cpp

${OBJECTDIR}/common/vector3.o: nbproject/Makefile-${CND_CONF}.mk common/vector3.cpp 
	${MKDIR} -p ${OBJECTDIR}/common
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/common/vector3.o common/vector3.cpp

${OBJECTDIR}/BspNode.o: nbproject/Makefile-${CND_CONF}.mk BspNode.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/BspNode.o BspNode.cpp

${OBJECTDIR}/TextureLoader.o: nbproject/Makefile-${CND_CONF}.mk TextureLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/TextureLoader.o TextureLoader.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/win32Release
	${RM} dist/win32Release/MinGW-Windows/learnbsp.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
