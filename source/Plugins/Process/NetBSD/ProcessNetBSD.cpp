//===-- ProcessNetBSD.cpp ----------------------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// C Includes
#include <errno.h>

// C++ Includes
// Other libraries and framework includes
#include "lldb/Core/PluginManager.h"
#include "lldb/Core/State.h"
#include "lldb/Host/Host.h"
#include "lldb/Symbol/ObjectFile.h"
#include "lldb/Target/DynamicLoader.h"
#include "lldb/Target/Target.h"

#include "ProcessNetBSD.h"
#include "ProcessPOSIXLog.h"
#include "Plugins/Process/Utility/InferiorCallPOSIX.h"
#include "Plugins/Process/Utility/NetBSDSignals.h"
#include "ProcessMonitor.h"
#include "NetBSDThread.h"

using namespace lldb;
using namespace lldb_private;

namespace
{
    UnixSignalsSP&
    GetNetBSDSignals ()
    {
        static UnixSignalsSP s_freebsd_signals_sp (new NetBSDSignals ());
        return s_freebsd_signals_sp;
    }
}

//------------------------------------------------------------------------------
// Static functions.

lldb::ProcessSP
ProcessNetBSD::CreateInstance(Target& target,
                               Listener &listener,
                               const FileSpec *crash_file_path)
{
    lldb::ProcessSP process_sp;
    if (crash_file_path == NULL)
        process_sp.reset(new ProcessNetBSD (target, listener));
    return process_sp;
}

void
ProcessNetBSD::Initialize()
{
    static bool g_initialized = false;

    if (!g_initialized)
    {
        PluginManager::RegisterPlugin(GetPluginNameStatic(),
                                      GetPluginDescriptionStatic(),
                                      CreateInstance);
        Log::Callbacks log_callbacks = {
            ProcessPOSIXLog::DisableLog,
            ProcessPOSIXLog::EnableLog,
            ProcessPOSIXLog::ListLogCategories
        };

        Log::RegisterLogChannel (ProcessNetBSD::GetPluginNameStatic(), log_callbacks);
        ProcessPOSIXLog::RegisterPluginName(GetPluginNameStatic());
        g_initialized = true;
    }
}

lldb_private::ConstString
ProcessNetBSD::GetPluginNameStatic()
{
    static ConstString g_name("freebsd");
    return g_name;
}

const char *
ProcessNetBSD::GetPluginDescriptionStatic()
{
    return "Process plugin for NetBSD";
}

//------------------------------------------------------------------------------
// ProcessInterface protocol.

lldb_private::ConstString
ProcessNetBSD::GetPluginName()
{
    return GetPluginNameStatic();
}

uint32_t
ProcessNetBSD::GetPluginVersion()
{
    return 1;
}

void
ProcessNetBSD::GetPluginCommandHelp(const char *command, Stream *strm)
{
}

Error
ProcessNetBSD::ExecutePluginCommand(Args &command, Stream *strm)
{
    return Error(1, eErrorTypeGeneric);
}

Log *
ProcessNetBSD::EnablePluginLogging(Stream *strm, Args &command)
{
    return NULL;
}

//------------------------------------------------------------------------------
// Constructors and destructors.

ProcessNetBSD::ProcessNetBSD(Target& target, Listener &listener)
    : ProcessPOSIX(target, listener, GetNetBSDSignals ()),
      m_resume_signo(0)
{
}

void
ProcessNetBSD::Terminate()
{
}

Error
ProcessNetBSD::DoDetach(bool keep_stopped)
{
    Error error;
    if (keep_stopped)
    {
        error.SetErrorString("Detaching with keep_stopped true is not currently supported on NetBSD.");
        return error;
    }

    error = m_monitor->Detach(GetID());

    if (error.Success())
        SetPrivateState(eStateDetached);

    return error;
}

Error
ProcessNetBSD::DoResume()
{
    Log *log (ProcessPOSIXLog::GetLogIfAllCategoriesSet (POSIX_LOG_PROCESS));

    SetPrivateState(eStateRunning);

    Mutex::Locker lock(m_thread_list.GetMutex());
    bool do_step = false;

    if (log)
        log->Printf("process %" PRIu64 " resuming (%s)", GetID(), do_step ? "step" : "continue");
    if (do_step)
        m_monitor->SingleStep(GetID(), m_resume_signo);
    else
        m_monitor->Resume(GetID(), m_resume_signo);

    return Error();
}

bool
ProcessNetBSD::UpdateThreadList(ThreadList &old_thread_list, ThreadList &new_thread_list)
{
    Log *log (ProcessPOSIXLog::GetLogIfAllCategoriesSet (POSIX_LOG_PROCESS));
    if (log)
        log->Printf("ProcessNetBSD::%s (pid = %" PRIu64 ")", __FUNCTION__, GetID());

    return true;
}

Error
ProcessNetBSD::WillResume()
{
    m_resume_signo = 0;
    m_suspend_tids.clear();
    m_run_tids.clear();
    m_step_tids.clear();
    return ProcessPOSIX::WillResume();
}

void
ProcessNetBSD::SendMessage(const ProcessMessage &message)
{
    Mutex::Locker lock(m_message_mutex);

    switch (message.GetKind())
    {
    case ProcessMessage::eInvalidMessage:
        return;

    case ProcessMessage::eAttachMessage:
        SetPrivateState(eStateStopped);
        return;

    case ProcessMessage::eLimboMessage:
    case ProcessMessage::eExitMessage:
        SetExitStatus(message.GetExitStatus(), NULL);
        break;

    case ProcessMessage::eSignalMessage:
    case ProcessMessage::eSignalDeliveredMessage:
    case ProcessMessage::eBreakpointMessage:
    case ProcessMessage::eTraceMessage:
    case ProcessMessage::eWatchpointMessage:
    case ProcessMessage::eCrashMessage:
        SetPrivateState(eStateStopped);
        break;

    case ProcessMessage::eNewThreadMessage:
        assert(0 && "eNewThreadMessage unexpected on NetBSD");
        break;

    case ProcessMessage::eExecMessage:
        SetPrivateState(eStateStopped);
        break;
    }

    m_message_queue.push(message);
}
