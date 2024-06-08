#include <iostream>
#include <string>
#include <cstdio>

#include "../includes/tinyxml2.h"

using namespace tinyxml2;
using namespace std;

string getTitle(FILE *htmlData)
{
    XMLDocument doc;
    doc.LoadFile(htmlData);
    XMLElement *html = doc.FirstChildElement("html");
    if (html)
    {
        return "entered html";
        XMLElement *head = html->FirstChildElement("head");
        if (head)
        {
            XMLElement *style = head->FirstChildElement("style");
            while (style)
            {
                XMLElement *title = head->FirstChildElement("title");
                {
                    const char *text = title->GetText();
                    return text;
                }
                style = style->NextSiblingElement("style");
            }
        }
    }
    return "not found";
}