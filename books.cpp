#include "book.h"
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;


Book::Book(): title(""), author(""), isbn(""), isAvailable(true), borrowerName("") {}

Book::Book(const string& title, const string& author, const string& isbn)
    : title(title), author(author), isbn(isbn), isAvailable(true), borrowerName("") {}


string Book::getTitle() const {return title;}

string Book::getAuthor() const {return author;}
string Book::getISBN() const {return isbn;}
bool Book::getAvailability() const {return isAvailable;}
string Book::getBorrowerName() const {return borrowerName;}

void Book::setTitle(const string& t) { title = t; }

void Book::setAuthor(const string& a) { author = a; }
void Book::setISBN(const string& i) { isbn = i; }
void Book::setAvailability(bool available) { isAvailable = available; }
void Book::setBorrowerName(const string& name) { borrowerName = name; }


void Book::checkOut(const string& borrower) {
    if (isAvailable) {
        isAvailable = false;
        borrowerName = borrower;
    }
}

void Book::returnBook() {
    isAvailable = true;
    borrowerName.clear();
}

string Book::toString() const {
    string s;
    s = "Titre : " + title
      + "\nAuteur : " + author
      + "\nISBN : " + isbn
      + "\nStatut : " + string(isAvailable ? "Disponible" : "Emprunté");
    if (!isAvailable && !borrowerName.empty()) {
        s += "\nEmprunté par : " + borrowerName;
    }
    return s;
}

string Book::toFileFormat() const {
    return title + "|" + author + "|" + isbn + "|" + (isAvailable ? "1" : "0") + "|" + borrowerName;
}

void Book::fromFileFormat(const string& line) {
    if (line.empty()) return;

    stringstream ss(line);
    string availStr;

    getline(ss, title, '|');
    getline(ss, author, '|');
    getline(ss, isbn, '|');
    getline(ss, availStr, '|');
    getline(ss, borrowerName, '|');

    if (availStr == "0" || availStr == "false" || availStr == "False") {
        isAvailable = false;
    } else {
        isAvailable = true;
    }

    if (isAvailable) borrowerName.clear();
}