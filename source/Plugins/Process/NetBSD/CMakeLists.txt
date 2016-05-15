include_directories(.)
include_directories(../POSIX)
include_directories(../Utility)

add_lldb_library(lldbPluginProcessNetBSD
  ProcessNetBSD.cpp
  NetBSDThread.cpp
  ProcessMonitor.cpp

  POSIXStopInfo.cpp
  RegisterContextPOSIXProcessMonitor_x86.cpp
  )
