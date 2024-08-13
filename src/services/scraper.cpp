#include "scraper.hpp"

using namespace std;

PyObject *initialize_python()
{
	// declare local variables
	vector<string> result;
	FILE *py_script;

	// initialize Python Environment
	Py_NoSiteFlag = 1;
	Py_SetProgramName("app0:eboot.bin");
	setenv("PYTHONHOME", "app0:", 1);
	setenv("HOME", "app0:", 1);
	Py_Initialize();
	PySys_SetPath("app0:lib/python27.zip");

	// python file and dictionary handling
	py_script = fopen("app0:lib/services/scraper.py", "r");
	PyObject *p_main_module = PyImport_AddModule("__main__");
	PyObject *p_global_dict = PyModule_GetDict(p_main_module);

	// get the result of the scraping from the python script
	PyRun_SimpleFile(py_script, "scraper.py");
	fclose(py_script);

	// return global dictionary
	return p_main_module;
}

string recieve_search_results_from_python(char *markup, vector<Search_Result> *search_results)
{
	// get the string variable from the global dictionary
	PyObject *p_main_module = initialize_python();
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
				PyObject *p_title_utf8 = PyUnicode_AsUTF8String(p_title);
				const char *title = PyString_AsString(p_title_utf8);

				// extract the URL
				PyObject *p_url = PyTuple_GetItem(p_item, 1);
				PyObject *p_url_str = PyObject_Str(p_url);
				const char *url = PyString_AsString(p_url_str);

				// create a search_results object
				Search_Result new_search_result(title, url);
				search_results->push_back(new_search_result);
			}
		}
		// Return result
		Py_Finalize();
		return "Success";
	}
	else
	{
		Py_Finalize();
		return "Failed to get data from the html file";
	}
	return "";
}

string recieve_article_from_python(char *markup, vector<pair<string, vector<string>>> *article)
{

	// get the string variable from the global dictionary
	PyObject *p_main_module = initialize_python();
	PyObject *p_func = PyObject_GetAttrString(p_main_module, "get_article");
	PyObject *p_markup = PyString_FromString(markup);

	if (p_markup == nullptr)
	{
		Py_Finalize();
		return "Failed to create Python string from C++ string";
	}

	// check p_func exists and is a callable function
	if (p_func && PyCallable_Check(p_func))
	{
		PyObject *p_args = PyTuple_New(1);
		PyTuple_SetItem(p_args, 0, p_markup);

		// call function
		PyObject *p_article = PyObject_CallObject(p_func, p_args);

		for (int i = 0; i < PyList_Size(p_article); i++)
		{
			PyObject *p_item = PyList_GetItem(p_article, i); // get the tuple
			PyObject *p_key = PyTuple_GetItem(p_item, 0);	 // get the header
			PyObject *p_value = PyTuple_GetItem(p_item, 1);	 // get the paragraph list
			vector<string> paragraphs;						 // vector to store the paragraphs for each header

			// get header from tuple
			PyObject *c_key_utf8 = PyUnicode_AsUTF8String(p_key);
			const char *c_key = PyString_AsString(c_key_utf8);
			string cpp_key = c_key;
			cout << "The cpp_key is " << cpp_key << endl;

			// loop through paragraph list
			for (int j = 0; j < PyList_Size(p_value); j++)
			{
				PyObject *p_paragraph = PyList_GetItem(p_value, j); // get the pargraph

				// convert the pargraph and append it to the paragraph vector
				PyObject *c_value_utf8 = PyUnicode_AsUTF8String(p_paragraph);
				const char *c_value = PyString_AsString(c_value_utf8);
				string cpp_value = c_value;
				paragraphs.push_back(cpp_value);
			}
			// append the header and corresponding paragraphs to the dictionary
			article->push_back(make_pair(cpp_key, paragraphs));
			// clear paragraphs vector
			paragraphs.clear();
		}

		// convert the Python list to a C++ vector of strings
		Py_Finalize();
		return "Success";
	}
	else
	{
		Py_Finalize();
		return "Failed to get data from the html file";
	}
	Py_Finalize();
	return "";
}