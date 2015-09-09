//===-- HostThreadNetBSD.cpp -----------------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// lldb Includes
#include "lldb/Host/netbsd/HostThreadNetBSD.h"
#include "lldb/Host/Host.h"

// C includes
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sysctl.h>
#include <sys/user.h>

// C++ includes
#include <string>

using namespace lldb_private;

HostThreadNetBSD::HostThreadNetBSD()
{
}

HostThreadNetBSD::HostThreadNetBSD(lldb::thread_t thread)
    : HostThreadPosix(thread)
{
}

void
HostThreadNetBSD::GetName(lldb::tid_t tid, llvm::SmallVectorImpl<char> &name)
{
    pthread_t ptid;
    ::memcpy(&ptid, &tid, std::min(sizeof(ptid), sizeof(tid)));
    char buf[PTHREAD_MAX_NAMELEN_NP];
    ::pthread_getname_np(ptid, buf, PTHREAD_MAX_NAMELEN_NP);

    name.clear();
    name.append(buf, buf + strlen(buf));
}
