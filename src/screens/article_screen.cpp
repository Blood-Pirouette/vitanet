#include "article_screen.hpp" // header file

// namespace
using namespace std;

string textWrap(string paragraph, int location, int constant)
{
	int n = paragraph.rfind(' ', location);

	if (location >= paragraph.length())
	{
		return paragraph;
	}
	else
	{
		paragraph.at(n) = '\n';
		return textWrap(paragraph, location + constant, constant);
	}
}

void articleScreen(map<string, vector<string>> *article)
{
	// declare local variables
	SceCtrlData pad; // monitor trackpad presses
	vita2d_font *text_font = vita2d_load_font_file("app0:assets/font.ttf");
	map<string, vector<string>>::iterator it = article->begin(); // initialize an iterator
	int p_i = 0;												 // initialize a paragraph tracker

	// continuously draw choices and keep track of selection
	while (it != article->end())
	{

		// every frame draw the headers
		vita2d_start_drawing();
		vita2d_clear_screen();
		vita2d_draw_line(0.0, 100.0, 960.0, 100.0, TEXT_COLOR); // header split

		// monitor vita pad
		sceCtrlPeekBufferPositive(0, &pad, 1);
		if (pad.buttons & SCE_CTRL_CROSS)
		{
			if (p_i == (it->second).size() - 1)
			{
				it++;	 // increment the iterator
				p_i = 0; // reset the paragraph tracker
			}
			else
			{
				p_i++; // increment the paragraph tracker
			}
		}

		// draw the header in the page
		string header = it->first;
		vita2d_font_draw_text(text_font, 30, 70, TEXT_COLOR, 40, header.c_str());

		// draw the paragraph
		string raw_paragraph = (it->second)[p_i];
		string wrapped_paragraph = textWrap(raw_paragraph, 80, 80);
		vita2d_font_draw_text(text_font, 10, 140, TEXT_COLOR, 26, wrapped_paragraph.c_str());

		// end drawing and swap buffers
		vita2d_end_drawing();
		vita2d_swap_buffers();

		// defines how frequently the screen should be refreshed
		sceKernelDelayThread(0.15 * 1000 * 1000);
	}
}
