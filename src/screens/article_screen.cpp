#include "article_screen.hpp" // header file

// namespace
using namespace std;

void articleScreen(map<string, vector<string>> *article)
{

	vita2d_font *text_font = vita2d_load_font_file("app0:assets/font.ttf");

	// continuously draw choices and keep track of selection
	while (true)
	{

		// every frame draw the headers
		vita2d_start_drawing();
		vita2d_clear_screen();

		int y_pos = 0; // initialize y_pos as 0
		map<string, vector<string>>::iterator it = article->begin(); // create an iterator

		// draw the headers in the page
		for (it; it != article->end(); it++)
		{
			string key = it->first;
			vita2d_font_draw_text(text_font, 50, 130 + y_pos * 50, TEXT_COLOR, 20, key.c_str());
			y_pos++;
		}

		// end drawing and swap buffers
		vita2d_end_drawing();
		vita2d_swap_buffers();

		// defines how frequently the screen should be refreshed
		sceKernelDelayThread(0.15 * 1000 * 1000);
	}
}
