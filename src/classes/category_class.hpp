#ifndef CATEGORY_H
#define CATEGORY_H
#include <string>

using namespace std;
class Category
{
    public:
        string name = "";
        string category_url = "";
        Category(string name_parameter, string category_url_parameter){
            name = name_parameter;
            category_url = category_url_parameter;
        }
};

#endif // CATEGORY_H