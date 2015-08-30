//===-- NetBSDThread.h -----------------------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef liblldb_NetBSDThread_H_
#define liblldb_NetBSDThread_H_

// Other libraries and framework includes
#include "POSIXThread.h"

//------------------------------------------------------------------------------
// @class NetBSDThread
// @brief Abstraction of a NetBSD thread.
class NetBSDThread
    : public POSIXThread
{
public:

    //------------------------------------------------------------------
    // Constructors and destructors
    //------------------------------------------------------------------
    NetBSDThread(lldb_private::Process &process, lldb::tid_t tid);

    virtual ~NetBSDThread();

    //--------------------------------------------------------------------------
    // NetBSDThread internal API.

    // POSIXThread override
    virtual void
    WillResume(lldb::StateType resume_state);
};

#endif // #ifndef liblldb_NetBSDThread_H_
