#include "home_screen.hpp" // header file

// namespace
using namespace std;

void homePage()
{
	// constant macro
	const int BODY_TXT_X_POS = 480;
	const int BODY_TXT_Y_POS = 272;
	const int BODY_TXT_SIZE = 32;
	const string WELCOME_MESSAGE = "Press X to search for an article or O to exit the app";
	
	// declare local variables
	SceCtrlData pad; // monitor trackpad presses
	vita2d_font *text_font = vita2d_load_font_file("app0:assets/font.ttf");

	// Wait for user choice
	while (true)
	{
		// Every frame Draw The Title
		vita2d_start_drawing();
		vita2d_clear_screen();
		vita2d_font_draw_text(text_font, BODY_TXT_X_POS, BODY_TXT_Y_POS, TEXT_COLOR, BODY_TXT_SIZE, WELCOME_MESSAGE.c_str());

		// Track user input with the selection variable
		sceCtrlPeekBufferPositive(0, &pad, 1);
		if (pad.buttons & SCE_CTRL_CROSS)
		{
			break;
		}
		else if (pad.buttons & SCE_CTRL_CIRCLE)
		{
			sceKernelExitProcess(0);
		}
		// End drawing and swap buffers
		vita2d_end_drawing();
		vita2d_swap_buffers();

		// Defines how frequently the screen should be refreshed
		sceKernelDelayThread(0.15 * 1000 * 1000);
	}
}
