#include "Library.hpp"
#include <iostream>
#include "Book.hpp"
#include <Global.hpp>

using std::getline;
using std::ifstream;
using std::string;
using std::stoi;
using std::stoll;

Library::Library()
{
    books = new BookList();
}
Library::Library(BookList *books)
{
    this->books = books;
}

void Library::addBook(Book *book)
{
    books->push_back(book);
}
void Library::removeBook(ISBN_t ISBN)
{
    for (int i = 0; i < books->size(); i++)
    {
        if (books->at(i)->getISBN() == ISBN)
        {
            books->erase(books->begin() + i);
            return;
        }
    }
    throw std::invalid_argument("Book not found");
}
void Library::updateBook(ISBN_t ISBN, Book *book)
{
    for (int i = 0; i < books->size(); i++)
    {
        if (books->at(i)->getISBN() == ISBN)
        {
            books->at(i) = book;
            break;
        }
    }
}

Book *Library::getBook(ISBN_t ISBN)
{
    for (int i = 0; i < books->size(); i++)
    {
        if (books->at(i)->getISBN() == ISBN)
        {
            return books->at(i);
        }
    }
    return NULL;
}
BookList *Library::getBooks()
{
    return books;
}

void Library::saveFile(const string &fileName)
{
    ofstream file;
    file.open(fileName);
    if (!file.is_open())
    {
        std::invalid_argument("Error opening file: " + fileName);
        return;
    }
    for (int i = 0; i < books->size(); i++)
    {
        file << books->at(i)->getTitle() << delimiter
             << books->at(i)->getAuthor() << delimiter
             << books->at(i)->getYear() << delimiter
             << books->at(i)->getISBN() << std::endl;
    }
    file.close();
}
void Library::readFile(const string &fileName)
{
    ifstream file(fileName);
    if (file.is_open())
    {
        string line;
        while (std::getline(file, line))
        {
            vector<string> tokens = helpers::split(line, delimiter);
            Book *book = new Book(tokens[0], tokens[1],
                                  stoi(tokens[2]), stoll(tokens[3]));
            this->books->push_back(book);
        }
        file.close();
    }
    else
    {
        std::invalid_argument("File not found");
    }
}
void Library::printBooks()
{
    Book* book;
    for (int i = 0; i < books->size(); i++)
    {
        book = books->at(i);
        std::cout << book->getTitle()
                  << " " << delimiter << " "
                  << book->getISBN()
                  << std::endl;
    }
}

bool Library::exists(ISBN_t ISBN)
{
    return getBook(ISBN) != nullptr;
}
