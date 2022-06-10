#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

namespace constants
{
    const string booksDb = "db/booksDb.csv";
};

namespace helpers
{
    vector<string> split(const string &str, char delimiter);
}
