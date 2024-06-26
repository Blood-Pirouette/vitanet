#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <python2.7/Python.h>



using namespace std;

string getTitle(const char *markup)
{

	Py_SetProgramName("app0:eboot.bin");
	setenv("PYTHONHOME", "app0:", 1);
	Py_Initialize();
	PyRun_SimpleString("import sys\nsys.path.append('ux0:/data/lib/python2.7')\nsys.path.append('ux0:/data/lib/python27.zip')\n");  // Add support for External Modules
	PyRun_SimpleString("import os\n");
	PyRun_SimpleString("print os.name\n");
	PyRun_SimpleString("print sys.platform\n");
	PyRun_SimpleString("print sys.path\n");
	PyRun_SimpleString("print sys.builtin_module_names\n");
	Py_Finalize();
	return "";
}
