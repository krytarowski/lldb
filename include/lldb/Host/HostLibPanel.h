//===-- LibPanel.h ------------------------------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#pragma once

#ifndef LLDB_DISABLE_CURSES

#ifdef HAVE_CURSES_LIBPANEL
#include <panel.h>
#elif defined(__NetBSD__)
#include <lldb/Host/netbsd/libpanel/panel.h>
#else
#error "Missing libpanel(3) in your installation"
#endif

#endif
