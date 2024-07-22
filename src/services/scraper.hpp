#ifndef SCRAPER_H
#define SCRAPER_H

#include <iostream>
#include <string>
#include <vector>

#include <Python.h>
#include "../classes/category_class.hpp"

using namespace std;

string getCategory(vector<Category>*, const char *);
string recieve_categories_from_python(const char*, vector<Category>*, PyObject *);
 
#endif