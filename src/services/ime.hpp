#ifndef IME_H
#define IME_H

#include <stdio.h>
#include <cstring> //strcpy

// vita2d library
#include <vita2d.h>

#include <psp2/ime_dialog.h> 
#include <psp2/libime.h> //SceImeOpen
#include <psp2/sysmodule.h>  //sceSysmoduleLoadModule
#include <psp2/display.h> //sceDisplayWaitVblankStart
#include <codecvt>  //UTF conversion
#include <locale> //UTF conversion

void getUserInput(char*);

#endif