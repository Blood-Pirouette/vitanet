// standard libraries
#include <vector>
#include <stdlib.h>

// vita2d library
#include <vita2d.h>
#include <utility> //std::pair

// psp2 libraries
#include <psp2/kernel/threadmgr.h> //sceKernelExitProcess

// include classes
#include "classes/search_result_class.hpp"
// include services
#include "services/ime.cpp"
#include "services/libcurl.cpp"
#include "services/scraper.cpp"
// include screens
#include "screens/home_screen.cpp"
#include "screens/search_screen.cpp"
#include "screens/article_screen.cpp"

// namespace
using namespace std;

// constant macro
const int BUFFER_SIZE = 1000 * 1024;
string user_input_search;

// function prototypes
void scrapeSearchResultPage(vector<Search_Result> *);
void scrapeArticlePage(vector<pair<string, vector<string>>> *);

int main()
{
	char user_input[SCE_IME_MAX_TEXT_LENGTH + 1] = {0};
	vector<Search_Result> search_results;		  // a list called search_results of Search_Result objects
	vector<pair<string, vector<string>>> article; // a dictionary containing the scraped article with the header and associated paragraphs

	// initialize the network and the screen
	vita2d_init();
	vita2d_set_clear_color(RGBA8(255, 255, 255, 255));

	// show the home page
	homePage();

	// show the search screen
	getUserInput(user_input);

	// find matching articles
	user_input_search = user_input;
	string search_url = "https://en.wikipedia.org/w/index.php?search=" + user_input_search + "&title=Special:Search&profile=advanced&fulltext=1&ns0=1";
	cout << "Searching for: " << search_url << endl; // debug

	// download the search page
	download(search_url);

	// scrape the search results page
	scrapeSearchResultPage(&search_results);

	// start the search results page and track user selection
	int selection = searchResultsScreen(&search_results);

	// download the article page
	string corrected_url = "https://en.wikipedia.org" + search_results[selection].article_url;
	download(corrected_url);

	// scrape the article page
	scrapeArticlePage(&article);

	// start the article page
	articleScreen(&article);

	// Exit the app
	sceKernelExitProcess(0);
	return 0;
}

void scrapeSearchResultPage(vector<Search_Result> *search_results)
{
	// declare variables
	char *htmlbuffer = (char *)malloc(BUFFER_SIZE);
	string file_location = "ux0:data/vitanet/index.html";

	// File handling
	SceUID fd = sceIoOpen(file_location.c_str(), SCE_O_RDONLY, 0777);
	sceIoRead(fd, htmlbuffer, BUFFER_SIZE);
	htmlbuffer[BUFFER_SIZE - 1] = '\0';

	// Scrape site and get results
	string error = recieve_search_results_from_python(htmlbuffer, search_results);
}

void scrapeArticlePage(vector<pair<string, vector<string>>> *article)
{
	char *htmlbuffer = (char *)malloc(BUFFER_SIZE);
	string file_location = "ux0:data/vitanet/index.html";

	// File handling
	SceUID fd = sceIoOpen(file_location.c_str(), SCE_O_RDONLY, 0777);
	sceIoRead(fd, htmlbuffer, BUFFER_SIZE);
	htmlbuffer[BUFFER_SIZE - 1] = '\0';

	// Scrape site and get results
	string error = recieve_article_from_python(htmlbuffer, article);
}