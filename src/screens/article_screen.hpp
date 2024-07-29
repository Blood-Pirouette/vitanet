#ifndef ARTICLE_H
#define ARTICLE_H

// standard libraries
#include <string>

// vita2d library
#include <vita2d.h> //vita2d modules

// psp2 libraries
#include <psp2/ctrl.h>             //sceCtrlPeekBufferPositive, SceCtrlData
#include <psp2/kernel/threadmgr.h> //sceKernelDelayThread

void articleScreen(std::string);

#endif