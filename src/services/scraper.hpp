#ifndef SCRAPER_H
#define SCRAPER_H

#include <iostream>
#include <string>
#include <vector>
#include <Python.h>
#include "../classes/category_class.hpp"

using namespace std;

string getCategory(vector<Category>*, const char *);
string convert_to_python(const char *, PyObject *);
string recieve_from_python(vector<Category>*, PyObject *);
 
 #endif