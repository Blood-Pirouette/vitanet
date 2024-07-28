#ifndef SCRAPER_H
#define SCRAPER_H

#include <iostream>
#include <string>
#include <vector>

#include <Python.h>
#include "../classes/search_result_class.hpp"

using namespace std;

string getSearchResults(vector<Search_Result>*, const char *);
string recieve_search_results_from_python(const char*, vector<Search_Result>*, PyObject *);
 
#endif