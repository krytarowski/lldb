//===-- NetBSDSignals.h ----------------------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef liblldb_NetBSDSignals_H_
#define liblldb_NetBSDSignals_H_

// Project includes
#include "lldb/Target/UnixSignals.h"

/// NetBSD specific set of Unix signals.
class NetBSDSignals
    : public lldb_private::UnixSignals
{
public:
    NetBSDSignals();

private:
    void
    Reset();
};

#endif // liblldb_NetBSDSignals_H_
