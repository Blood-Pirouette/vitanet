#include "search_screen.hpp"

// namespace
using namespace std;

// constant macro
const int X_POS = 50;
const int HEADER_TXT_SIZE = 32;
const int LIST_TXT_SIZE = 20;
const int NO_LISTS_PAGE = 8;

// global variables
vita2d_font *text_font; // defines font
SceCtrlData pad;		// monitor trackpad presses

int searchResultsScreen(vector<Search_Result> *search_results)
{
	int selection = 0;
	int page = 0; // used to track current list page
	text_font = vita2d_load_font_file("app0:assets/font.ttf");

	// continuously draw choices and keep track of selection
	while (true)
	{
		// every frame draw the title 
		vita2d_start_drawing();
		vita2d_clear_screen();
		vita2d_font_draw_text(text_font, X_POS, 60, RGBA8(0x8E, 0x0A, 0xC0, 0xFF), HEADER_TXT_SIZE, "Search Results");
		vita2d_font_draw_text(text_font, X_POS, 90, RGBA8(0x8E, 0x0A, 0xC0, 0xFF), HEADER_TXT_SIZE, to_string(selection).c_str());
		// track current page
		int list_start = page * NO_LISTS_PAGE;	   // track the beginning of the list
		int list_end = NO_LISTS_PAGE * (page + 1) + 1; // track the end of the list

		// track user input with the selection variable 
		sceCtrlPeekBufferPositive(0, &pad, 1);
		if (pad.buttons & SCE_CTRL_DOWN)
		{
			selection++;
		}
		else if (pad.buttons & SCE_CTRL_UP)
		{
			selection--;
		}
		else if (pad.buttons & SCE_CTRL_RIGHT)
		{
			if (list_end < search_results->size())
			{
				page++;
				selection = list_start;
			}
		}
		else if (pad.buttons & SCE_CTRL_LEFT)
		{
			if (page > 0)
			{
				page--;
			}
			selection = list_start;
		}
		else if (pad.buttons & SCE_CTRL_CROSS)
		{
			return selection;
		}
		// check if we reached the beginning of the list or the end
		if (selection < list_start || selection >= list_end)
		{
			selection = list_start;
		}
		// check if list_end reaches out of search_results range
		if (list_end >= search_results->size())
		{
			list_end = search_results->size() - 1;
		}
		// every frame draw all title for each Search_Result object in the search_results list 
		for (int i = list_start; i < list_end; i++)
		{
			if (i == selection)
			{
				vita2d_font_draw_text(text_font, X_POS, 100 + ((i - page * NO_LISTS_PAGE) * 50), RGBA8(0x0A, 0xC0, 0x2B, 0xFF), LIST_TXT_SIZE, (*search_results)[i].title.c_str());
			}
			else
			{
				vita2d_font_draw_text(text_font, X_POS, 100 + ((i - page * NO_LISTS_PAGE) * 50), RGBA8(0xFF, 0xFF, 0xFF, 0xFF), LIST_TXT_SIZE, (*search_results)[i].title.c_str());
			}
		}

		// end drawing and swap buffers
		vita2d_end_drawing();
		vita2d_swap_buffers();

		// defines how frequently the screen should be refreshed
		sceKernelDelayThread(0.15 * 1000 * 1000);
	}
	return 1;
}
