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
const int BODY_TXT_X_POS = 50;
const int BODY_TXT_Y_POS = 50;
const int BODY_TXT_SIZE = 32;
const string WELCOME_MESSAGE = "Press X to search for an article or O to exit the app";

void homePage();

#endif