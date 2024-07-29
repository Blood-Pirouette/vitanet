#include "article_screen.hpp"

// namespace
using namespace std;

void articleScreen(string url)
{

	vita2d_font *text_font = vita2d_load_font_file("app0:assets/font.ttf");

	// continuously draw choices and keep track of selection
	while (true)
	{
		// every frame draw the title
		vita2d_start_drawing();
		vita2d_clear_screen();
		vita2d_font_draw_text(text_font, 50, 60, RGBA8(0x8E, 0x0A, 0xC0, 0xFF), 32, url.c_str());

		// end drawing and swap buffers
		vita2d_end_drawing();
		vita2d_swap_buffers();

		// defines how frequently the screen should be refreshed
		sceKernelDelayThread(0.15 * 1000 * 1000);
	}
}
