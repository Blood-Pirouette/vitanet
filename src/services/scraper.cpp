#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <Python.h>

using namespace std;

string getTitle(const char *markup)
{
	// Declare local variables
	string my_string = "";
	FILE *py_script;

	// Initialize Python Environment
	Py_NoSiteFlag = 1;
	Py_SetProgramName("app0:eboot.bin");
	setenv("PYTHONHOME", "app0:", 1);
	setenv("HOME", "app0:", 1);
	Py_Initialize();
	PySys_SetPath("app0:lib/python27.zip");

	py_script = fopen("app0:lib/services/scraper.py", "r");

	// Explicitly define the __main__ module
	PyObject *pMainModule = PyImport_AddModule("__main__");
	
	// Import all variables from the global namespace
	PyObject *pGlobalDict = PyModule_GetDict(pMainModule);

	// Run the script and free the file pointer
	PyRun_SimpleFile(py_script, "scraper.py");
	fclose(py_script);

	// Get the string variable from the global dictionary
	PyObject *pValue = PyDict_GetItemString(pGlobalDict, "my_string");

	// Check pValue is not null and that it is a string
	if (pValue && PyString_Check(pValue))
	{
		// Convert the Python string to a C string
		char *myString = PyString_AsString(pValue);
		my_string = string(myString);
	}
	else
	{
		return "Failed to get data from the html file";
	}

	Py_Finalize();

	return my_string;
}
