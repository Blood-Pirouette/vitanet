#ifndef SEARCH_RESULT_H
#define SEARCH_RESULT_H
#include <string>

using namespace std;
class Search_Result
{
    public:
        string title = "";
        string article_url = "";
        Search_Result(string title_parameter, string article_url_parameter){
            title = title_parameter;
            article_url = article_url_parameter;
        }
};

#endif