#ifndef ARTICLE_H
#define ARTICLE_H

// standard libraries
#include <string>
#include <vector>
#include <map>

// vita2d library
#include <vita2d.h> //vita2d modules

// psp2 libraries
#include <psp2/ctrl.h>             //sceCtrlPeekBufferPositive, SceCtrlData
#include <psp2/kernel/threadmgr.h> //sceKernelDelayThread

#define TEXT_COLOR RGBA8(0x00, 0x00, 0x00, 0xFF)

string textWrap(string, int, int);
void articleScreen(map<string, vector<string>> *);

#endif