#ifndef IME_H
#define IME_H

#include <stdio.h>

// vita2d library
#include <vita2d.h>

#include <psp2/ime_dialog.h> 
#include <psp2/libime.h> //SceImeOpen
#include <psp2/sysmodule.h>  //sceSysmoduleLoadModule
#include <psp2/display.h> //sceDisplayWaitVblankStart

void UTFConversion(uint8_t*, uint16_t*, int);
void getUserInput(uint8_t*);

#endif