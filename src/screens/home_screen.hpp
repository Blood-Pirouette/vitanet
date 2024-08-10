#ifndef HOME_H
#define HOME_H

// standard library
#include <string>

// vita2d library
#include <vita2d.h>

// psp2 libraries
#include <psp2/ctrl.h>              //sceCtrlPeekBufferPositive, SceCtrlData
#include <psp2/kernel/threadmgr.h>  //sceKernelDelayThread
#include <psp2/kernel/processmgr.h> //sceeKernelExitProcess

// constant macro
#define TEXT_COLOR RGBA8(0x00, 0x00, 0x00, 0xFF)

void homePage();

#endif