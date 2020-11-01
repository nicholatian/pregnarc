##############################################################################
##                                 PregNARC                                 ##
##                                                                          ##
##                    Copyright © 2020 Alexander Nicholi                    ##
##                Released under Mozilla Public License 2.0.                ##
##############################################################################

include $(AQ)/lib/slick/base.mk

# name of project. used in output binary naming
PROJECT := pregnarc

# put a ‘1’ for the desired target types to compile
EXEFILE :=
SOFILE  :=
AFILE   := 1

# space-separated path list for #includes
# <system> includes
INCLUDES := include
# "local" includes
INCLUDEL := src

# space-separated library name list
LIBS    := uni
LIBDIRS :=

# frameworks (macOS target only)
FWORKS :=

# ‘3P’ are in-tree 3rd-party dependencies
# 3PLIBDIR is the base directory
# 3PLIBS is the folder names in the base directory for each library
3PLIBDIR := 3rdparty
3PLIBS   :=

# sources
CFILES    := \
	src/narc.c
CPPFILES  :=
PUBHFILES := \
	include/pregnarc.h
PRVHFILES :=

# test suite sources
TES_CFILES    :=
TES_CPPFILES  :=
TES_PUBHFILES :=
TES_PRVHFILES :=

# this defines all our usual targets
include $(AQ)/lib/slick/targets.mk
