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

void articleScreen(vector<pair<string, vector<string>>> *article)
{
	// declare local variables
	SceCtrlData pad; // monitor trackpad presses
	vita2d_font *text_font = vita2d_load_font_file("app0:assets/font.ttf");
	int h_i = 0; // initialize a header tracker
	int p_i = 0; // initialize a paragraph tracker
	int article_size = article->size();

	// continuously draw choices and keep track of selection
	while (h_i < article_size)
	{
		// every frame draw the headers
		vita2d_start_drawing();
		vita2d_clear_screen();
		vita2d_draw_line(0.0, 60.0, 960.0, 60.0, TEXT_COLOR); // header split
		pair<string, vector<string>> item = (*article)[h_i];  // get pair item

		// monitor vita pad
		sceCtrlPeekBufferPositive(0, &pad, 1);

		// monitor pad keys
		if ((pad.buttons & SCE_CTRL_CROSS) && h_i < article_size - 1)
		{
			modifyTracker(article_size, &item, &h_i, &p_i, 1); //move to next header/paragraph
		}
		else if (pad.buttons & SCE_CTRL_TRIANGLE)
		{
			modifyTracker(article_size, &item, &h_i, &p_i, 0); //move to previous header/paragraph

		}
		else if (pad.buttons & SCE_CTRL_CIRCLE)
		{
			break; //exit app
		}

		// draw the header in the page
		string header = get<0>(item);
		vita2d_font_draw_text(text_font, 20, 50, TEXT_COLOR, 40, header.c_str());

		// draw the paragraph
		string raw_paragraph = get<1>(item)[p_i];
		string wrapped_paragraph = textWrap(raw_paragraph, 70, 70);
		vita2d_font_draw_text(text_font, 2, 90, TEXT_COLOR, 24, wrapped_paragraph.c_str());

		// end drawing and swap buffers
		vita2d_end_drawing();
		vita2d_swap_buffers();

		// defines how frequently the screen should be refreshed
		sceKernelDelayThread(0.15 * 1000 * 1000);
	}
}

void modifyTracker(int size, pair<string, vector<string>> *item, int *h_i, int *p_i, int direction)
{
	if (direction == 1)
	{
		if (*p_i == get<1>(*item).size() - 1)
		{
			(*h_i)++;	  // increment the header iterator
			*p_i = 0; // reset the paragraph tracker
		}
		else
		{
			(*p_i)++; // increment the paragraph tracker
		}
	}
	else if (direction == 0)
	{
		if (*h_i > 0)
		{
			(*h_i)--;	 // go back to the previous header
			*p_i = 0; // reset pargraph tracker to 0
		}
	}
}
