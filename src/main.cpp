// standard libraries
#include <vector>

// vita2d library
#include <vita2d.h>

// psp2 libraries
#include <psp2/kernel/threadmgr.h>  //sceKernelExitProcess

// Include classes
#include "classes/category_class.hpp"
// Include services
#include "services/scraper.cpp"
#include "services/libcurl.cpp"
// Include screens
#include "screens/main_screen.cpp"


// namespace
using namespace std;

// constant macro
const int BUFFER_SIZE = 100 * 1024;

// function prototypes
string categoriesInit(vector<Category> *, char *);

int main()
{
	vector<Category> categories; // A list called categories of Category objects
	int selection; // Used to track user selection

	/* Initialize the network and the screen */
	download();
	vita2d_init();
	vita2d_set_clear_color(RGBA8(0, 0, 0, 255));

	// Initialize the categories list
	char htmlbuffer[BUFFER_SIZE];
	string error = categoriesInit(&categories, htmlbuffer);

	// Start the main page
	selection = mainPage(&categories);
	
	// Exit the app
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
