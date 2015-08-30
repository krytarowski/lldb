//===-- NetBSDSignals.cpp --------------------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// C Includes
// C++ Includes
// Other libraries and framework includes
// Project includes
#include "NetBSDSignals.h"

NetBSDSignals::NetBSDSignals()
    : UnixSignals()
{
    Reset();
}

void
NetBSDSignals::Reset()
{
    UnixSignals::Reset();

    //        SIGNO  NAME         SHORT NAME SUPPRESS STOP   NOTIFY DESCRIPTION 
    //        ====== ============ ========== ======== ====== ====== ===================================================
    AddSignal (32,   "SIGTHR",    "THR",     false,   true , true , "thread interrupt");
    AddSignal (33,   "SIGLIBRT",  "LIBRT",   false,   true , true , "reserved by real-time library");
}
