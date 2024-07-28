#include <assert.h>
#include <algorithm>
#include <vector>
#include <string.h>

#include <iostream>
#include <stdlib.h>

#include <Python.h>
#include "scraper.hpp"
#include "../classes/search_result_class.hpp"

using namespace std;

string recieve_search_results_from_python(const char *markup, vector<Search_Result> *search_results, PyObject *p_main_module)
{
	// get the string variable from the global dictionary
	PyObject *p_func = PyObject_GetAttrString(p_main_module, "get_search_results");
	PyObject *p_markup = PyString_FromString(markup);

	if (p_markup == nullptr)
	{
		Py_Finalize();
		return "Failed to create Python string from C++ string";
	}

	// check p_func exists and is a callable function
	if (p_func && PyCallable_Check(p_func))
	{

		PyObject *p_markup = PyString_FromString(markup);
		PyObject *p_args = PyTuple_New(1);
		PyTuple_SetItem(p_args, 0, p_markup);

		// call function
		PyObject *p_search_result_list = PyObject_CallObject(p_func, p_args);

		// convert the Python list to a C++ vector of strings
		for (int i = 0; i < PyList_Size(p_search_result_list); ++i)
		{
			PyObject *p_item = PyList_GetItem(p_search_result_list, i);
			if (PyTuple_Check(p_item) && PyTuple_Size(p_item) == 2)
			{
				// extract the title
				PyObject *p_title = PyTuple_GetItem(p_item, 0);
				PyObject *p_title_str = PyObject_Str(p_title);
				const char *title = PyString_AsString(p_title_str);

				// extract the URL
				PyObject *p_url = PyTuple_GetItem(p_item, 1);
				PyObject *p_url_str = PyObject_Str(p_url);
				const char *url = PyString_AsString(p_url_str);

				// create a search_results object
				Search_Result new_search_result(title, url);
				search_results->push_back(new_search_result);
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

string getSearchResults(vector<Search_Result> *search_results, const char *markup)
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
	error = recieve_search_results_from_python(markup, search_results, p_main_module);

	// Return result
	Py_Finalize();
	return "";
}
