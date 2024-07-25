// standard libraries
#include <vector>

// vita2d library
#include <vita2d.h>

// psp2 libraries
#include <psp2/kernel/threadmgr.h> //sceKernelExitProcess

// Include classes
#include "classes/category_class.hpp"
// Include services
#include "services/ime.cpp"
#include "services/libcurl.cpp"
#include "services/scraper.cpp"
// Include screens
#include "screens/home_screen.cpp"
#include "screens/search_screen.cpp"

// namespace
using namespace std;

// constant macro
const int BUFFER_SIZE = 100 * 1024;
string user_input_search;
string url = "https://en.wikipedia.org/w/index.php?search=" + user_input_search + "&title=Special:Search&profile=advanced&fulltext=1&ns0=1";

// function prototypes
string categoriesInit(vector<Category> *, char *);

int main()
{
	char user_input[SCE_IME_MAX_TEXT_LENGTH + 1] = {0};
	vector<Category> categories; // A list called categories of Category objects
	int selection;				 // Used to track user selection

	// Initialize the network and the screen
	vita2d_init();
	vita2d_set_clear_color(RGBA8(0, 0, 0, 255));

	// show th home page
	homePage();

	// show the search screen
	getUserInput(user_input);
	while(true){
		cout << user_input;
	}

	// download the user request
	//user_input_search = user_input;
	downloadPage(url, "/" + user_input_search);

	// Initialize the categories list
	char htmlbuffer[BUFFER_SIZE];
	string error = categoriesInit(&categories, htmlbuffer);

	// Start the main page
	selection = searchResults(&categories);

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
