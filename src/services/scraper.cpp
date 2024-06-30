
#include <assert.h>
#include <algorithm>
#include <vector>
#include <string.h>

#include <iostream>
#include <stdlib.h>

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
string recieve_from_python(vector<string> *result_array, PyObject *p_global_dict)
{
	// Get the string variable from the global dictionary
	PyObject *p_result = PyDict_GetItemString(p_global_dict, "category_items");

	// Check pValue is not null and that it is a string
	if (p_result && PyList_Check(p_result))
	{
		// Convert the Python list to a C++ vector of strings
		for (Py_ssize_t i = 0; i < PyList_Size(p_result); ++i)
		{
			PyObject *p_item = PyList_GetItem(p_result, i);
			if (PyString_Check(p_item))
			{
				result_array->push_back(PyString_AsString(p_item));
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

string getTitle(vector<string> *result_array, const char *markup)
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
	error = recieve_from_python(result_array, p_global_dict);

	// Return result
	Py_Finalize();
	return error;
}
