#ifndef SCRAPER_H
#define SCRAPER_H

#include <iostream>
#include <string>
#include <vector>
#include <utility>

#include <Python.h>
#include "../classes/search_result_class.hpp"

using namespace std;

/*
Initialize Python 2.7

Returns global dictionary
*/
PyObject* initialize_python();

/*
Takes two arguments:
1) c string containing the html markup
1) vector<Search_Result> pointer to store the search results

Returns error message, if any
*/
string recieve_search_results_from_python(char *, vector<Search_Result> *);

/*
Takes two arguments:
1) c string containing the html markup
1) vector<pair<string, vector<string>>> pointer to store the scraped article

Returns error message, if any
*/
string recieve_article_from_python(char *, vector<pair<string, vector<string>>> *);

#endif