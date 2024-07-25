#include "ime.hpp"

using namespace std;

void getUserInput(char* user_input)
{
    // local variables
    int dialog = 0; // default ime dialog show status
    uint16_t utf16_user_input[SCE_IME_DIALOG_MAX_TEXT_LENGTH + 1]; //store user input in utf16

    // UTF conversion for the title
    string utf8_title = "Enter search keyword";
    u16string utf16_title = wstring_convert<codecvt_utf8_utf16<char16_t>, char16_t>{}.from_bytes(utf8_title.data());
    
    // load required module
    sceSysmoduleLoadModule(SCE_SYSMODULE_IME);

    while (1)
    {
        if (!dialog)
        {
            // initialize dialog parametes
            SceImeDialogParam param;
            sceImeDialogParamInit(&param);
           
            // set parameters for ime
            param.type = SCE_IME_DIALOG_TEXTBOX_MODE_DEFAULT;
            param.title = (const SceWChar16 *)utf16_title.c_str();
            param.inputTextBuffer = utf16_user_input;
            param.maxTextLength = SCE_IME_DIALOG_MAX_TEXT_LENGTH;

            // initialize dialog and flag the dialog status
            sceImeDialogInit(&param);
            dialog = 1;
        }
        vita2d_start_drawing();
        vita2d_clear_screen();

        // get status of the ime dialog
        SceCommonDialogStatus ime_status = sceImeDialogGetStatus();
        if (ime_status == 2) // if the enter key is pressed
        {
            // UTF conversion for the input text buffer
            u16string utf16_user_str = (char16_t *)utf16_user_input;
            string utf8_user_input = wstring_convert<codecvt_utf8_utf16<char16_t>, char16_t>{}.to_bytes(utf16_user_str.data());
	        
            // copy the string to user_input and go back to the main function
            strcpy(user_input, utf8_user_input.c_str());
            break;
        }

        vita2d_end_drawing();
        vita2d_common_dialog_update();
        vita2d_swap_buffers();
        sceDisplayWaitVblankStart();
    }
}