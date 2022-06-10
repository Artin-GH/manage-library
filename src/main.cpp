#include <iostream>
#include "Library.hpp"
#include "Book.hpp"
#include "Global.hpp"

using namespace std;

enum Option
{
    ADD_BOOK = 1,
    REMOVE_BOOK,
    FIND_BOOK,
    PRINT_BOOKS,
    UPDATE_BOOK,
    EXIT
};

namespace state
{
    Library library;
    Book *book;
    string title, author, yearStr, isbnStr;
    Year_t year;
    ISBN_t isbn;
}

namespace reader
{
    void readTitle(const string &prefix, bool canSkip)
    {
        cout << prefix << " title: ";
        getline(cin, state::title);
        if (canSkip && state::title.empty())
        {
            state::title = state::library.getBook(state::isbn)->getTitle();
            return;
        }
        if (state::title.empty()) readTitle(prefix, false);
    }

    void readAuthor(const string &prefix, bool canSkip)
    {
        cout << prefix << " author: ";
        getline(cin, state::author);
        if (canSkip && state::author.empty())
        {
            state::author = state::library.getBook(state::isbn)->getAuthor();
            return;
        }
        if (state::author.empty()) readAuthor(prefix, false);
    }

    void readYear(const string &prefix, bool canSkip)
    {
        cout << prefix << " year: ";
        getline(cin, state::yearStr);
        if (canSkip && state::yearStr.empty())
        {
            state::year = state::library.getBook(state::isbn)->getYear();
            return;
        }
        try
        {
            state::year = stoi(state::yearStr);
        }
        catch (const exception &e)
        {
            readYear(prefix, canSkip);
        }
    }

    void readISBN(const string &prefix, bool canSkip)
    {
        cout << prefix << " ISBN: ";
        getline(cin, state::isbnStr);
        if (canSkip && state::isbnStr.empty())
        {
            state::isbn = state::library.getBook(state::isbn)->getISBN();
            return;
        }
        try
        {
            state::isbn = stoll(state::isbnStr);
        }
        catch (const exception &e)
        {
            readISBN(prefix, canSkip);
        }
    }

    void readISBNExists(const string &prefix)
    {
        readISBN(prefix, false);
        if (!state::library.exists(state::isbn))
        {
            readISBNExists(prefix);
        }
    }
};

namespace operations
{
    void addBook()
    {
        cin.ignore();
        reader::readTitle("Enter", false);
        reader::readAuthor("Enter", false);
        reader::readYear("Enter", false);
        reader::readISBN("Enter", false);

        state::book = new Book(state::title, state::author,
                               state::year, state::isbn);
        state::library.addBook(state::book);
    }

    void removeBook()
    {
        cin.ignore();
        reader::readISBNExists("Enter");
        state::library.removeBook(state::isbn);
    }

    void findBook()
    {
        cin.ignore();
        reader::readISBNExists("Enter");
        cout << endl
             << state::library.getBook(state::isbn)->toString()
             << endl;
    }

    void printBooks()
    {
        state::library.printBooks();
    }

    void updateBook()
    {
        cin.ignore();
        reader::readISBNExists("Enter");
        ISBN_t oldIsbn = state::isbn;
        Book* oldBook = state::library.getBook(oldIsbn);

        reader::readTitle("Enter new", true);
        reader::readAuthor("Enter new", true);
        reader::readYear("Enter new", true);
        reader::readISBN("Enter new", true);

        state::library.updateBook(state::isbn, new Book(state::title,
                                  state::author, state::year, state::isbn));
    }

    void exitApp()
    {
        state::library.saveFile(constants::booksDb);
        exit(EXIT_SUCCESS);
    }
}

void printMenu()
{
    cout << "Select an option: " << endl
         << "1. Add a book" << endl
         << "2. Remove a book" << endl
         << "3. Search for a book" << endl
         << "4. Print all books" << endl
         << "5. Update a book" << endl
         << "6. Exit" << endl
         << "Option: ";
}

void optionOperator(Option option)
{
    switch (option)
    {
    case ADD_BOOK: operations::addBook(); break;
    case REMOVE_BOOK: operations::removeBook(); break;
    case FIND_BOOK: operations::findBook(); break;
    case PRINT_BOOKS: operations::printBooks(); break;
    case UPDATE_BOOK: operations::updateBook(); break;
    case EXIT: operations::exitApp(); break;
    default: cout << "Invalid option" << endl; break;
    }
}

int main()
{
    short option;

    state::library.readFile(constants::booksDb);

    while (true)
    {
        printMenu();

        cin >> option;
        cout << endl;

        optionOperator((Option) option);
        cout << endl << endl;
    }

    return EXIT_SUCCESS;
}
