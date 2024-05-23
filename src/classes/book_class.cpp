#include <string>
using namespace std;
class Book
{
    public:
        std::string title = "";
        std::string book_url = "";
        Book(string title_parameter, string book_url_parameter){
            title = title_parameter;
            book_url = book_url_parameter;
        }
};