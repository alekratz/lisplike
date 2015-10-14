#include "util.hpp"

using namespace std;

string pad_internal(const ll_children& terms, cstref inner)
{
    string result = "";
    for(auto it = terms.begin(); it != terms.end(); it++)
    {
        if(it + 1 == terms.end())
            result += (*it)->gencode();
        else
            result += (*it)->gencode() + inner;
    }
    return result;
}