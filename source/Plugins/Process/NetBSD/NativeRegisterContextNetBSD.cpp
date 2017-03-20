//===-- NativeRegisterContextNetBSD.cpp --------------------------*- C++
//-*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "NativeRegisterContextNetBSD.h"

using namespace lldb_private;
using namespace lldb_private::process_netbsd;

NativeRegisterContextNetBSD::NativeRegisterContextNetBSD(
    NativeThreadProtocol &native_thread, uint32_t concrete_frame_idx,
    RegisterInfoInterface *reg_info_interface_p)
    : NativeRegisterContextRegisterInfo(native_thread, concrete_frame_idx,
                                        reg_info_interface_p) {}

lldb::ByteOrder NativeRegisterContextNetBSD::GetByteOrder() const {
  return lldb::eByteOrderInvalid;
}

Error NativeRegisterContextNetBSD::ReadGPR() { return Error(); }

Error NativeRegisterContextNetBSD::WriteGPR() { return Error(); }

Error NativeRegisterContextNetBSD::ReadFPR() { return Error(); }

Error NativeRegisterContextNetBSD::WriteFPR() { return Error(); }

Error NativeRegisterContextNetBSD::DoReadGPR(void *buf) { return Error(); }

Error NativeRegisterContextNetBSD::DoWriteGPR(void *buf) { return Error(); }

Error NativeRegisterContextNetBSD::DoReadFPR(void *buf) { return Error(); }

Error NativeRegisterContextNetBSD::DoWriteFPR(void *buf) { return Error(); }

NativeProcessNetBSD &NativeRegisterContextNetBSD::GetProcess() {
  auto process_sp =
      std::static_pointer_cast<NativeProcessNetBSD>(m_thread.GetProcess());
  assert(process_sp);
  return *process_sp;
}

::pid_t NativeRegisterContextNetBSD::GetProcessPid() { return -1; }
