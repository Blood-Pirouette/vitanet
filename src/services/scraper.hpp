#ifndef SCRAPER_H
#define SCRAPER_H

#include <iostream>
#include <string>
#include <vector>
#include <map>



#include <Python.h>
#include "../classes/search_result_class.hpp"

using namespace std;


/*
Takes two inputs:
1) vector<Search_Result> pointer to store the search results
2) c string containing the html markup

Returns error message, if any
*/
string getSearchResults(vector<Search_Result>*, const char *);

/*
Takes three inputs:
1) c string containing the html markup
1) vector<Search_Result> pointer to store the search results
2) PyObject pointing to dictionary

Returns error message, if any
*/
string recieve_search_results_from_python(const char*, vector<Search_Result>*, PyObject *);

/*
Takes three inputs:
1) c string containing the html markup
1) map<string, vector<string>> pointer to store the scraped article
2) PyObject pointing to dictionary

Returns error message, if any
*/
string recieve_article_from_python(const char*, vector<Search_Result>*, PyObject *);



#endif