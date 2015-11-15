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

#if !defined(__NetBSD__)
#include <panel.h>
#else
#include <lldb/Host/netbsd/libpanel/panel.h>
#endif

#endif
