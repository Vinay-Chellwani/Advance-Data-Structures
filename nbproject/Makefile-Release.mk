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
CND_PLATFORM=Cygwin-Windows
CND_DLIB_EXT=dll
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/BTree.o \
	${OBJECTDIR}/Skip\ List\ implementation.o \
	${OBJECTDIR}/Skip\ list\ assignment.o \
	${OBJECTDIR}/VEB.o \
	${OBJECTDIR}/b_tree.o \
	${OBJECTDIR}/binomial_heap.o \
	${OBJECTDIR}/fibonaccci_project.o \
	${OBJECTDIR}/kd_tree.o \
	${OBJECTDIR}/kd_tree1.o \
	${OBJECTDIR}/point_region_quad_tree.o \
	${OBJECTDIR}/position_heap.o \
	${OBJECTDIR}/quad_tree.o \
	${OBJECTDIR}/rbtins.o \
	${OBJECTDIR}/red\ black\ trees.o \
	${OBJECTDIR}/red-black.o \
	${OBJECTDIR}/skip_list.o \
	${OBJECTDIR}/veb_updated.o


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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/advance_data_structures.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/advance_data_structures.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/advance_data_structures ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/BTree.o: BTree.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/BTree.o BTree.c

.NO_PARALLEL:${OBJECTDIR}/Skip\ List\ implementation.o
${OBJECTDIR}/Skip\ List\ implementation.o: Skip\ List\ implementation.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Skip\ List\ implementation.o Skip\ List\ implementation.cpp

.NO_PARALLEL:${OBJECTDIR}/Skip\ list\ assignment.o
${OBJECTDIR}/Skip\ list\ assignment.o: Skip\ list\ assignment.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Skip\ list\ assignment.o Skip\ list\ assignment.cpp

${OBJECTDIR}/VEB.o: VEB.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/VEB.o VEB.c

${OBJECTDIR}/b_tree.o: b_tree.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/b_tree.o b_tree.cpp

${OBJECTDIR}/binomial_heap.o: binomial_heap.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/binomial_heap.o binomial_heap.cpp

${OBJECTDIR}/fibonaccci_project.o: fibonaccci_project.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/fibonaccci_project.o fibonaccci_project.cpp

${OBJECTDIR}/kd_tree.o: kd_tree.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kd_tree.o kd_tree.cpp

${OBJECTDIR}/kd_tree1.o: kd_tree1.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kd_tree1.o kd_tree1.cpp

${OBJECTDIR}/point_region_quad_tree.o: point_region_quad_tree.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/point_region_quad_tree.o point_region_quad_tree.cpp

${OBJECTDIR}/position_heap.o: position_heap.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/position_heap.o position_heap.cpp

${OBJECTDIR}/quad_tree.o: quad_tree.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/quad_tree.o quad_tree.cpp

${OBJECTDIR}/rbtins.o: rbtins.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/rbtins.o rbtins.cpp

.NO_PARALLEL:${OBJECTDIR}/red\ black\ trees.o
${OBJECTDIR}/red\ black\ trees.o: red\ black\ trees.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/red\ black\ trees.o red\ black\ trees.c

${OBJECTDIR}/red-black.o: red-black.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/red-black.o red-black.cpp

${OBJECTDIR}/skip_list.o: skip_list.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/skip_list.o skip_list.cpp

${OBJECTDIR}/veb_updated.o: veb_updated.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/veb_updated.o veb_updated.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
