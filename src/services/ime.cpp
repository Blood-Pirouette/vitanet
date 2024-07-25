#include "ime.hpp"

using namespace std;

void getUserInput(char* user_input)
{
    // local variables
    int dialog = 0; // default ime dialog show status
    uint16_t utf16_user_input[SCE_IME_DIALOG_MAX_TEXT_LENGTH + 1]; //store user input in utf16

    // UTF conversion
    string utf8_title = "Enter search keyword";
    u16string utf16_title = wstring_convert<codecvt_utf8_utf16<char16_t>, char16_t>{}.from_bytes(utf8_title.data());
    
    // load required module
    sceSysmoduleLoadModule(SCE_SYSMODULE_IME);

    while (1)
    {
        if (!dialog)
        {
            SceImeDialogParam param;
            sceImeDialogParamInit(&param);
           
            param.type = SCE_IME_DIALOG_TEXTBOX_MODE_DEFAULT;
            param.title = (const SceWChar16 *)utf16_title.c_str();
            param.inputTextBuffer = utf16_user_input;
            param.maxTextLength = SCE_IME_DIALOG_MAX_TEXT_LENGTH;
            sceImeDialogInit(&param);
            dialog = 1;
        }
        vita2d_start_drawing();
        vita2d_clear_screen();

        SceCommonDialogStatus ime_status = sceImeDialogGetStatus();
        if (ime_status == 2)
        {
            u16string utf16_user_str = (char16_t *)utf16_user_input;
            string utf8_user_input = wstring_convert<codecvt_utf8_utf16<char16_t>, char16_t>{}.to_bytes(utf16_user_str.data());
	        strcpy(user_input, utf8_user_input.c_str());
            break;
        }

        vita2d_end_drawing();
        vita2d_common_dialog_update();
        vita2d_swap_buffers();
        sceDisplayWaitVblankStart();
    }
}