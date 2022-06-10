#include "Book.hpp"
#include <string>
#include "Global.hpp"

using std::string;
using std::to_string;

Book::Book()
{
    title = "";
    author = "";
    year = 0;
    ISBN = 0;
}
Book::Book(const string &title, const string &author, Year_t year, ISBN_t ISBN)
{
    setTitle(title);
    setAuthor(author);
    setYear(year);
    setISBN(ISBN);
}

void Book::setTitle(string title)
{
    this->title = title;
}
void Book::setAuthor(string author)
{
    this->author = author;
}
void Book::setYear(Year_t year)
{
    this->year = year;
}
void Book::setISBN(ISBN_t ISBN)
{
    this->ISBN = ISBN;
}

string Book::getTitle()
{
    return title;
}
string Book::getAuthor()
{
    return author;
}
Year_t Book::getYear()
{
    return year;
}
ISBN_t Book::getISBN()
{
    return ISBN;
}
string Book::toString()
{
    return "Title: " + title +
           "\nAuthor: " + author +
           "\nYear: " + to_string(year) +
           "\nISBN: " + to_string(ISBN);
}
