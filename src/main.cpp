#include <psp2/kernel/processmgr.h>
#include <sstream>
#include <vector>
#include <psp2/io/fcntl.h>
#include <vita2d.h>
#include <map>
#include <psp2/appmgr.h>
#include <psp2/io/stat.h>
#include <psp2/io/dirent.h>
#include <psp2/types.h>
#include <psp2/kernel/threadmgr.h>
#include <psp2/net/http.h>
#include <psp2/sysmodule.h>
#include <psp2/net/net.h>
#include <psp2/net/netctl.h>
#include <psp2/ctrl.h>

#include "services/scraper.hpp"
#include "classes/book_class.cpp"
#include "services/libcurl.cpp"

// namespace
using namespace std;

// function prototypes
//void netInit();
string scrape_site();
void booksInit(vector<Book> &books);

// global variable
vita2d_font *text_font;

int main(int argc, char *argv[])
{
	SceCtrlData pad;	// Will be used to monitor trackpad presses
	vector<Book> books; // A list called books of Book objects
	int selection = 0;	// Used to track user selection

	/* Initialize the screen */
	//netInit();
	download();
	vita2d_init();
	vita2d_set_clear_color(RGBA8(0, 0, 0, 255));
	text_font = vita2d_load_font_file("app0:assets/font.ttf");

	/*Initialize the books list*/
	booksInit(books);
	string scraped_text = scrape_site();

	// Continuously Draw Choices and Keep Track of Selection
	while (true)
	{
		/* Every frame Draw The Title */
		vita2d_start_drawing();
		vita2d_clear_screen();
		vita2d_font_draw_text(text_font, 200, 60, RGBA8(0x8E, 0x0A, 0xC0, 0xFF), 32, "Books");
		vita2d_font_draw_text(text_font, 200, 90, RGBA8(0x8E, 0x0A, 0xC0, 0xFF), 32, scraped_text.c_str());

		/* Track User Pressing UP/DOWN/CROSS with the selection variable */
		sceCtrlPeekBufferPositive(0, &pad, 1);
		if (pad.buttons & SCE_CTRL_DOWN)
		{

			selection += 1;
		}
		else if (pad.buttons & SCE_CTRL_UP)
		{
			selection -= 1;
		}
		else if (pad.buttons & SCE_CTRL_CROSS)
		{
			// open books page
		}
		if (selection > 4 || selection < 0)
		{
			selection = 0;
		}

		/* Every frame draw all title for each Book object in the books list */
		for (int i = 0; i < 5; i++)
		{
			if (i == selection)
			{
				vita2d_font_draw_text(text_font, 200, 100 + (i * 50), RGBA8(0x0A, 0xC0, 0x2B, 0xFF), 10, books[i].title.c_str());
			}
			else
			{
				vita2d_font_draw_text(text_font, 200, 100 + (i * 50), RGBA8(0xFF, 0xFF, 0xFF, 0xFF), 10, books[i].title.c_str());
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

string scrape_site()
{
	const char *htmlData = "<div><p>Some text</p></div>";

	return getTitle(htmlData);
}

void booksInit(vector<Book> &books)
{
	for (int i = 0; i < 5; i++)
	{
		Book new_book(to_string(i), "placeholder");
		books.push_back(new_book);
	}
	books[0].book_url = "book1.html";
	books[1].book_url = "book2.html";
	books[2].book_url = "book3.html";
}

