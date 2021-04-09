#include "JSONFormatter.h"


void JSONFormatter::outFormat(CompositeFunction* cf)
{
    json j;
    to_json(j, *cf);
    std::ofstream o(filePath);
    o << j << std::endl;
}

void JSONFormatter::inFormat(CompositeFunction* cf)
{
    json j;
    std::ifstream i(filePath);
    if (!i.is_open()) {
        cout << "GRESKA" << endl;
        return;
    }
    i >> j;
    from_json(j, *cf);
}

void JSONFormatter::outFormat(Image* im)
{
    json j;
    to_json(j, *im);
    std::ofstream o(filePath);
    o << j << std::endl;

}

void JSONFormatter::inFormat(Image* im)
{
    json j;
    std::ifstream i(filePath);
    if (!i.is_open()) {
        cout << "GRESKA" << endl;
        return;
    }
    i >> j;
    from_json(j, *im);
}
