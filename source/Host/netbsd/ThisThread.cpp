//===-- ThisThread.cpp ------------------------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "lldb/Host/HostNativeThread.h"
#include "lldb/Host/ThisThread.h"

#include "llvm/ADT/SmallVector.h"

#include <pthread.h>
#include <string.h>

using namespace lldb_private;

void
ThisThread::SetName(llvm::StringRef name)
{
    ::pthread_setname_np(::pthread_self(), "%s", const_cast<char*>(name.data()));
}

void
ThisThread::GetName(llvm::SmallVectorImpl<char> &name)
{
    ::pthread_t ptid = ::pthread_self();
    uint64_t threadId = 0;
    ::memcpy(&threadId, &ptid, std::min(sizeof(threadId), sizeof(ptid)));
    HostNativeThread::GetName((lldb::tid_t)threadId, name);
}
