#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <python3.11/Python.h>

using namespace std;

string getTitle(const char *markup)
{
    Py_Initialize();
    const char *pythonCode = "example_string = 'Hello world'";
    PyRun_SimpleString(pythonCode);

    PyObject *pyString = PyDict_GetItemString(PyModule_GetDict(PyImport_AddModule("__main__")), "example_string");
    const char *cppString = PyUnicode_AsUTF8(pyString);
    return cppString;
}
