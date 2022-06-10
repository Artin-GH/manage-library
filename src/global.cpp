#include "Global.hpp"
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::stringstream;

vector<string> helpers::split(const string &str, char delimitor)
{
    int8_t start = 0;
    int8_t end = str.find(delimitor);
    vector<string> result;
    while (end != -1)
    {
        result.push_back(str.substr(start, end - start));
        start = end + sizeof(delimitor);
        end = str.find(delimitor, start);
    }
    result.push_back(str.substr(start, end - start));
    return result;
}
