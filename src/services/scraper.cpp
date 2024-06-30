#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <Python.h>

using namespace std;

string convert_to_python(const char *markup, PyObject *p_global_dict)
{

	// Set the C++ string as a Python variable in the global dictionary
	PyObject *p_markup = PyString_FromString(markup);
	if (p_markup == nullptr)
	{
		Py_Finalize();
		return "Failed to create Python string from C++ string";
	}

	PyDict_SetItemString(p_global_dict, "markup", p_markup);
	Py_DECREF(p_markup);
	return "";
}
string recieve_from_python(PyObject *p_global_dict)
{

	// Get the string variable from the global dictionary
	PyObject *p_result = PyDict_GetItemString(p_global_dict, "result");

	// Check pValue is not null and that it is a string
	if (p_result && PyString_Check(p_result))
	{
		// Convert the Python string to a C string
		char *result = PyString_AsString(p_result);
		return string(result);
	}
	else
	{
		return "Failed to get data from the html file";
	}
	return "";
}

string getTitle(const char *markup)
{
	// Declare local variables
	string result = "";
	FILE *py_script;

	// Initialize Python Environment
	Py_NoSiteFlag = 1;
	Py_SetProgramName("app0:eboot.bin");
	setenv("PYTHONHOME", "app0:", 1);
	setenv("HOME", "app0:", 1);
	Py_Initialize();
	PySys_SetPath("app0:lib/python27.zip");

	// Python file and dictionary handling
	py_script = fopen("app0:lib/services/scraper.py", "r");
	PyObject *p_main_module = PyImport_AddModule("__main__");
	PyObject *p_global_dict = PyModule_GetDict(p_main_module);

	// Pass HTML markup for scraping to python script
	result = convert_to_python(markup, p_global_dict);

	// Get the result of the scraping from the python script
	PyRun_SimpleFile(py_script, "scraper.py");
	fclose(py_script);
	result = recieve_from_python(p_global_dict);

	// Return result
	Py_Finalize();
	return result;
}
