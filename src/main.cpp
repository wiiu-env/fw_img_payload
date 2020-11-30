#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <malloc.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <whb/log_udp.h>
#include <sysapp/launch.h>
#include <coreinit/title.h>

#include "utils/logger.h"
#include "dynamic.h"
#include "kernel.h"
#include "main.h"
#include "ios_exploit.h"

extern "C" void OSForceFullRelaunch();

extern "C" uint32_t _start(int argc, char **argv) {
    doKernelSetup();
    InitFunctionPointers();

    WHBLogUdpInit();

    DEBUG_FUNCTION_LINE("Hello from cfw_booter");
    
    ExecuteIOSExploit();
    
    revertMainHook();

    OSForceFullRelaunch();    
    SYSLaunchMenu();

    if (
            OSGetTitleID() == 0x000500101004A200L || // mii maker eur
            OSGetTitleID() == 0x000500101004A100L || // mii maker usa
            OSGetTitleID() == 0x000500101004A000L) {   // mii maker jpn
            
        DEBUG_FUNCTION_LINE("We are in mii maker");
        // return to mii maker.
        return ( (int (*)(int, char **))(*(unsigned int*)0x1005E040) )(argc, argv);
    } else {
        DEBUG_FUNCTION_LINE("We are in another payload");
        uint32_t result = 0;
        result |= 4; // Proc UI loop
        return result;
    }
    return 0;
}
