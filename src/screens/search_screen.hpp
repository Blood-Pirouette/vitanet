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

int searchResultsScreen(vector<Search_Result> *);

#endif