#pragma once

#include <vector>
#include "Book.hpp"
#include "Global.hpp"
#include <fstream>

using std::vector;
using std::ofstream;

typedef vector<Book *> BookList;

class Library
{
private:
    BookList *books;
    static const char delimiter = '|';

public:
    Library();
    Library(BookList *books);

    void addBook(Book *book);
    void removeBook(ISBN_t ISBN);
    void updateBook(ISBN_t ISBN, Book *book);
    void printBooks();

    Book *getBook(ISBN_t ISBN);
    BookList *getBooks();

    void saveFile(const string &fileName);
    void readFile(const string &fileName);

    bool exists(ISBN_t ISBN);
};
