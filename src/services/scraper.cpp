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

string recieve_categories_from_python(const char *markup, vector<Category> *categories, PyObject *p_main_module)
{
	// Get the string variable from the global dictionary
	// PyObject *p_result = PyDict_GetItemString(p_global_dict, "category_items_text");
	PyObject *p_func = PyObject_GetAttrString(p_main_module, "get_categories");
	PyObject *p_markup = PyString_FromString(markup);

	if (p_markup == nullptr)
	{
		Py_Finalize();
		return "Failed to create Python string from C++ string";
	}

	// Check p_func exists and is a callable function
	if (p_func && PyCallable_Check(p_func))
	{


		PyObject *p_markup = PyString_FromString(markup);
		PyObject *p_args = PyTuple_New(1);
		PyTuple_SetItem(p_args, 0, p_markup);
		PyObject *p_category_list = PyObject_CallObject(p_func, p_args);

		// Convert the Python list to a C++ vector of strings
		for (int i = 0; i < PyList_Size(p_category_list); ++i)
		{
			PyObject *p_item = PyList_GetItem(p_category_list, i);
			PyObject *p_item_str = PyObject_Str(p_item);
			if (PyString_Check(p_item_str))
			{
				Category new_category(PyString_AsString(p_item_str), "URL Holder");
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

	// Get the result of the scraping from the python script
	PyRun_SimpleFile(py_script, "scraper.py");
	fclose(py_script);
	error = recieve_categories_from_python(markup, categories, p_main_module);

	// Return result
	Py_Finalize();
	return "";
}
