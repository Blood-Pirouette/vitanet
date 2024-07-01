#include <assert.h>
#include <algorithm>
#include <vector>
#include <string.h>

#include <iostream>
#include <stdlib.h>

#include <Python.h>
#include "scraper.hpp"
#include "../classes/category_class.hpp"

using namespace std;

string convert_to_python(const char *markup, PyObject *p_global_dict)
{

	// Set the C++ string as a Python variable in the global namespace
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
string recieve_from_python(vector<Category> *categories, PyObject *p_global_dict)
{
	// Get the string variable from the global dictionary
	PyObject *p_result = PyDict_GetItemString(p_global_dict, "category_items_text");

	// Check p_result exists and is a list
	if (p_result && PyList_Check(p_result))
	{
		// Convert the Python list to a C++ vector of strings
		for (int i = 0; i < PyList_Size(p_result); ++i)
		{
			PyObject *p_item = PyList_GetItem(p_result, i);
			PyObject *p_item_str = PyObject_Str(p_item);
			if (PyString_Check(p_item_str))
			{
				Category new_category(PyString_AsString(p_item_str), "placeholder");
				categories->push_back(new_category);
			}
		}
		return "Success";
	}
	else
	{
		return "Failed to get data from the html file";
	}
	return "";
}

string getCategory(vector<Category> *categories, const char *markup)
{
	// Declare local variables
	vector<string> result;
	string error;
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
	error = convert_to_python(markup, p_global_dict);

	// Get the result of the scraping from the python script
	PyRun_SimpleFile(py_script, "scraper.py");
	fclose(py_script);
	error = recieve_from_python(categories, p_global_dict);

	// Return result
	Py_Finalize();
	return error;
}
