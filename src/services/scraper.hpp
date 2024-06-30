#include <iostream>
#include <string>
#include "scraper.cpp"
#include <Python.h>

using namespace std;

string getTitle(const char *);
string convert_to_python(const char *, PyObject *);
string recieve_from_python(PyObject *);
