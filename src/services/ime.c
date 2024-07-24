#include "ime.h"


/*
UTF8/16 conversion for 1 bytes
Choice 0 for utf8 -> utf16
Choice 1 for utf16 -> utf8
*/
void UTFConversion(uint8_t *utf8, uint16_t *utf16, int choice)
{
    switch (choice)
    {
    case 0:
        for (int i = 0; utf8[i]; ++i)
        {
            utf16[i] = utf8[i];
        }
        break;
    case 1:
        for (int i = 0; utf16[i]; ++i)
        {
            utf8[i] = utf16[i];
        }
        break;
    }
}

void getUserInput(uint8_t *utf8_user_input)
{
    // local variables
    int dialog = 0;                         // default ime dialog show status
    char *title = "Enter Text";             // title for ime dialog
    uint8_t *utf8_title = (uint8_t *)title; // utf8 title for ime dialog
    uint16_t utf16_title[SCE_IME_DIALOG_MAX_TITLE_LENGTH]; // declate utf16 title
    UTFConversion(utf8_title, utf16_title, 0); // convert utf8 title to utf16 title
    uint16_t utf16_user_input[SCE_IME_MAX_TEXT_LENGTH + 1] = {0};  // declare utf16_user_input
    SceWChar16 libime_out[SCE_IME_MAX_PREEDIT_LENGTH + SCE_IME_MAX_TEXT_LENGTH + 1];
    
    // load required module
    sceSysmoduleLoadModule(SCE_SYSMODULE_IME);

    
    while (1)
    {
        if (!dialog)
        {
            SceImeDialogParam param;
            sceImeDialogParamInit(&param);
            param.supportedLanguages = SCE_IME_LANGUAGE_ENGLISH;
            param.languagesForced = SCE_TRUE;
            param.type = SCE_IME_DIALOG_TEXTBOX_MODE_DEFAULT;
            param.option = 0;
            param.textBoxMode = SCE_IME_DIALOG_TEXTBOX_MODE_DEFAULT;
            param.title = (SceWChar16 *)utf16_title;
            param.maxTextLength = SCE_IME_DIALOG_MAX_TEXT_LENGTH;
            param.initialText = (SceWChar16 *)libime_out;
            param.inputTextBuffer = utf16_user_input;
            sceImeDialogInit(&param);
            dialog = 1;
        }
        vita2d_start_drawing();
        vita2d_clear_screen();

        SceCommonDialogStatus ime_status = sceImeDialogGetStatus();
        if (ime_status == 2)
        {
            UTFConversion(utf8_user_input, utf16_user_input, 1);
            break;
        }

        vita2d_end_drawing();
        vita2d_common_dialog_update();
        vita2d_swap_buffers();
        sceDisplayWaitVblankStart();
    }
}