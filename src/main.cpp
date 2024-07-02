#include <sstream>
#include <vector>
#include <map>
#include <stdio.h>

#include <vita2d.h>
#include <psp2/appmgr.h>
#include <psp2/types.h>
#include <psp2/ctrl.h>

#include <psp2/io/stat.h>
#include <psp2/io/dirent.h>
#include <psp2/io/fcntl.h>

#include <psp2/sysmodule.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/kernel/threadmgr.h>

#include <psp2/net/http.h>
#include <psp2/net/net.h>
#include <psp2/net/netctl.h>

#include "services/scraper.cpp"
#include "classes/category_class.hpp"
#include "services/libcurl.cpp"

// namespace
using namespace std;

// constant macro
const int BUFFER_SIZE = 100 * 1024;
const int X_POS = 50;
const int HEADER_TXT_SIZE = 32;
const int LIST_TXT_SIZE = 20;
const int NO_LISTS_PAGE = 8;

// function prototypes
// void netInit();
string categoriesInit(vector<Category> *, char *);

// global variable
vita2d_font *text_font;

int main()
{

	SceCtrlData pad;			 // Will be used to monitor trackpad presses
	vector<Category> categories; // A list called categories of Category objects
	int selection = 0;			 // Used to track user selection
	int page = 0;				 // Used to track current list page

	/* Initialize the screen */
	// netInit();
	download();
	vita2d_init();
	vita2d_set_clear_color(RGBA8(0, 0, 0, 255));
	text_font = vita2d_load_font_file("app0:assets/font.ttf");

	/*Initialize the categories list*/
	char htmlbuffer[BUFFER_SIZE];

	string error = categoriesInit(&categories, htmlbuffer);

	// Continuously draw choices and keep track of selection
	while (true)
	{
		/* Every frame Draw The Title */
		vita2d_start_drawing();
		vita2d_clear_screen();
		vita2d_font_draw_text(text_font, X_POS, 60, RGBA8(0x8E, 0x0A, 0xC0, 0xFF), HEADER_TXT_SIZE, "Books");
		vita2d_font_draw_text(text_font, X_POS, 90, RGBA8(0x8E, 0x0A, 0xC0, 0xFF), HEADER_TXT_SIZE, to_string(selection).c_str());
		/* Track current page */
		int list_start = page * NO_LISTS_PAGE + 1;	   // Track the beginning of the list
		int list_end = NO_LISTS_PAGE * (page + 1) + 1; // Track the end of the list

		/* Track user input with the selection variable */
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
			page++;
			selection = list_start;
		}
		else if (pad.buttons & SCE_CTRL_CROSS)
		{
			// open category page
		}
		// Check if we reached the beginning of the list or the end
		if (selection < list_start || selection > list_end)
		{
			selection = list_start;
		}
		// Check if list_end reaches out of categories range
		if (list_end >= categories.size())
		{
			list_end = categories.size() - 1;
		}
		/* Every frame draw all title for each Category object in the categories list */
		for (int i = list_start; i < list_end; i++)
		{
			if (i == selection)
			{
				vita2d_font_draw_text(text_font, X_POS, 100 + ((i - page * NO_LISTS_PAGE) * 50), RGBA8(0x0A, 0xC0, 0x2B, 0xFF), LIST_TXT_SIZE, categories[i].name.c_str());
			}
			else
			{
				vita2d_font_draw_text(text_font, X_POS, 100 + ((i - page * NO_LISTS_PAGE) * 50), RGBA8(0xFF, 0xFF, 0xFF, 0xFF), LIST_TXT_SIZE, categories[i].name.c_str());
			}
		}

		/* End drawing and swap buffers */
		vita2d_end_drawing();
		vita2d_swap_buffers();

		/*Defines how frequently the screen should be refreshed*/
		sceKernelDelayThread(0.15 * 1000 * 1000);
	}

	sceKernelExitProcess(0);
	return 0;
}

string categoriesInit(vector<Category> *categories, char *buffer)
{
	string error;
	const char *file = "ux0:data/vitanet/index.html";

	// File handling
	SceUID fd = sceIoOpen(file, SCE_O_RDONLY, 0777);
	sceIoRead(fd, buffer, BUFFER_SIZE);
	buffer[BUFFER_SIZE - 1] = '\0';

	// Scrape site and get results
	error = getCategory(categories, buffer);
	return error;
}
