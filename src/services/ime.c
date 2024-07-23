#include "ime.h"

void getUserInput()
{
    // local variables
    int dialog = 0;
    uint16_t user_input[SCE_IME_MAX_TEXT_LENGTH + 1] = {0};
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
            param.title = (SceWChar16 *)libime_out;
            param.maxTextLength = SCE_IME_DIALOG_MAX_TEXT_LENGTH;
            param.initialText = (SceWChar16 *)libime_out;
            param.inputTextBuffer = user_input;
            sceImeDialogInit(&param);
            dialog = 1;
        }
        vita2d_start_drawing();
        vita2d_clear_screen();

        vita2d_end_drawing();
        vita2d_common_dialog_update();
        vita2d_swap_buffers();
        sceDisplayWaitVblankStart();
    }
}