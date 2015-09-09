##===- source/Core/Makefile --------------------------------*- Makefile -*-===##
# 
#                     The LLVM Compiler Infrastructure
#
# This file is distributed under the University of Illinois Open Source
# License. See LICENSE.TXT for details.
# 
##===----------------------------------------------------------------------===##

LLDB_LEVEL := ../..

# It should be done with autotools
ifeq ($(HOST_OS),NetBSD)
	CPP.Flags += -DCURSES_HAVE_NCURSES_NCURSES_H
else
	CPP.Flags += -DCURSES_HAVE_NCURSES_H
endif

LIBRARYNAME := lldbCore
BUILD_ARCHIVE = 1

include $(LLDB_LEVEL)/Makefile
