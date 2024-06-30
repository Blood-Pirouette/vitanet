#include <iostream>
#include <string>
#include <vector>
#include "scraper.cpp"
#include <Python.h>

using namespace std;

string getTitle(vector<string>*, const char *);
string convert_to_python(const char *, PyObject *);
string recieve_from_python(vector<string>*, PyObject *);
 