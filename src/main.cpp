#include <fcntl.h>

#include <coreinit/exit.h>
#include <proc_ui/procui.h>
#include <whb/log_udp.h>
#include <sysapp/launch.h>
#include <coreinit/thread.h>
#include <coreinit/foreground.h>

#include "utils/logger.h"
#include "dynamic.h"
#include "kernel.h"
#include "ios_exploit.h"

extern "C" void OSForceFullRelaunch();

bool CheckRunning() {
    switch (ProcUIProcessMessages(true)) {
        case PROCUI_STATUS_EXITING: {
            return false;
        }
        case PROCUI_STATUS_RELEASE_FOREGROUND: {
            ProcUIDrawDoneRelease();
            break;
        }
        case PROCUI_STATUS_IN_FOREGROUND: {
            break;
        }
        case PROCUI_STATUS_IN_BACKGROUND:
        default:
            break;
    }
    return true;
}

extern "C" uint32_t _start(int argc, char **argv) {
    doKernelSetup();
    InitFunctionPointers();

    WHBLogUdpInit();
    DEBUG_FUNCTION_LINE("Hello from fw_img_payload");

    ExecuteIOSExploit();

    DEBUG_FUNCTION_LINE("IOSU Exploit done");

    OSForceFullRelaunch();
    SYSLaunchMenu();

    ProcUIInit(OSSavesDone_ReadyToRelease);
    while (CheckRunning()) {
        // wait.
        OSSleepTicks(OSMillisecondsToTicks(100));
    }
    ProcUIShutdown();

    DEBUG_FUNCTION_LINE("Byebye");
    _Exit(0);
    return 0;
}
