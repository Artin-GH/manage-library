#pragma once

#include <string>
#include "Global.hpp"

using std::string;

typedef uint16_t Year_t;
typedef uint64_t ISBN_t;

class Book
{
private:
    string title;
    string author;
    Year_t year;
    ISBN_t ISBN;

public:
    Book();
    Book(const string &title, const string &author, Year_t year, ISBN_t ISBN);

    void setTitle(string title);
    void setAuthor(string author);
    void setYear(Year_t year);
    void setISBN(ISBN_t ISBN);

    string getTitle();
    string getAuthor();
    Year_t getYear();
    ISBN_t getISBN();
    string toString();
};
