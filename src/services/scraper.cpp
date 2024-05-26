#include <iostream>
#include <string>

#include "../includes/tinyxml2.h"

using namespace tinyxml2;
using namespace std;


string getTitle(const char *htmlData)
{
    XMLDocument doc;
    doc.Parse(htmlData);
    XMLElement *div = doc.FirstChildElement("div");
    if (div)
    {
        XMLElement *p = div->FirstChildElement("p");
        if (p)
        {
            const char *text = p->GetText();
            return text;
        }
    }
    return "";
}