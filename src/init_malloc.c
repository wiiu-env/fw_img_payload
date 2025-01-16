void __init_wut_malloc();

void __preinit_user(void *outMem1,
               void *outFG,
               void *outMem2){
    __init_wut_malloc();
}
