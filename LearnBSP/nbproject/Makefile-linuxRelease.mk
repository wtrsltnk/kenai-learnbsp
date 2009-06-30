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
	${OBJECTDIR}/Application.o \
	${OBJECTDIR}/common/font.o \
	${OBJECTDIR}/common/camera.o \
	${OBJECTDIR}/BspObject.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/common/texture.o \
	${OBJECTDIR}/common/math3d.o \
	${OBJECTDIR}/common/data.o \
	${OBJECTDIR}/common/plane.o \
	${OBJECTDIR}/common/vector3.o \
	${OBJECTDIR}/BspNode.o

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
LDLIBSOPTIONS=-lglfw -lGLU -lpthread -lXrandr

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-linuxRelease.mk dist/linuxRelease/GNU-Linux-x86/learnbsp

dist/linuxRelease/GNU-Linux-x86/learnbsp: ${OBJECTFILES}
	${MKDIR} -p dist/linuxRelease/GNU-Linux-x86
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/learnbsp ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/Application.o: nbproject/Makefile-${CND_CONF}.mk Application.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Application.o Application.cpp

${OBJECTDIR}/common/font.o: nbproject/Makefile-${CND_CONF}.mk common/font.cpp 
	${MKDIR} -p ${OBJECTDIR}/common
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/common/font.o common/font.cpp

${OBJECTDIR}/common/camera.o: nbproject/Makefile-${CND_CONF}.mk common/camera.cpp 
	${MKDIR} -p ${OBJECTDIR}/common
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/common/camera.o common/camera.cpp

${OBJECTDIR}/BspObject.o: nbproject/Makefile-${CND_CONF}.mk BspObject.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/BspObject.o BspObject.cpp

${OBJECTDIR}/main.o: nbproject/Makefile-${CND_CONF}.mk main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/common/texture.o: nbproject/Makefile-${CND_CONF}.mk common/texture.cpp 
	${MKDIR} -p ${OBJECTDIR}/common
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/common/texture.o common/texture.cpp

${OBJECTDIR}/common/math3d.o: nbproject/Makefile-${CND_CONF}.mk common/math3d.cpp 
	${MKDIR} -p ${OBJECTDIR}/common
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/common/math3d.o common/math3d.cpp

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

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/linuxRelease
	${RM} dist/linuxRelease/GNU-Linux-x86/learnbsp

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
