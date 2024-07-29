#ifndef SEARCH_H
#define SEARCH_H

// standard libraries
#include <vector>

// vita2d library
#include <vita2d.h> //vita2d modules

// psp2 libraries
#include <psp2/ctrl.h>             //sceCtrlPeekBufferPositive, SceCtrlData
#include <psp2/kernel/threadmgr.h> //sceKernelDelayThread

// include classes
#include "../classes/search_result_class.hpp"

// constant macro
#define TEXT_COLOR RGBA8(0x00, 0x00, 0x00, 0xFF)
#define HIGHLIGHT_COLOR RGBA8(0x30, 0x95, 0xD9, 0xFF)
const int X_POS = 50;
const int HEADER_TXT_SIZE = 32;
const int LIST_TXT_SIZE = 20;
const int NO_LISTS_PAGE = 8;

int searchResultsScreen(vector<Search_Result> *);

#endif