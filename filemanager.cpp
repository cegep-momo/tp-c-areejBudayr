#include <fstream>
#include <iostream>
#include <filesystem>
#include <ctime>        // pour time_t, localtime, strftime
#include "filemanager.h"

using namespace std;

// Constructor
FileManager::FileManager(const string& booksFile, const string& usersFile, const string& logsFile)
    : booksFileName(booksFile), usersFileName(usersFile), logsFileName(logsFile) {}

// Save all library data
bool FileManager::saveLibraryData(Library& library) {
    return saveBooksToFile(library) && saveUsersToFile(library);
}

// Load all library data
bool FileManager::loadLibraryData(Library& library) {
    bool booksLoaded = loadBooksFromFile(library);
    bool usersLoaded = loadUsersFromFile(library);
    return booksLoaded || usersLoaded; // Return true if at least one file was loaded
}

// Save books to file
bool FileManager::saveBooksToFile(Library& library) {
    ofstream file(booksFileName);
    if (!file.is_open()) {
        cout << "Erreur : Impossible d'ouvrir " << booksFileName << " en écriture.\n";
        return false;
    }

    auto books = library.getAllBooks();
    for (Book* book : books) {
        file << book->toFileFormat() << "\n";
    }

    file.close();
    return true;
}

// Save users to file
bool FileManager::saveUsersToFile(Library& library) {
    ofstream file(usersFileName);
    if (!file.is_open()) {
        cout << "Erreur : Impossible d'ouvrir " << usersFileName << " en écriture.\n";
        return false;
    }

    auto users = library.getAllUsers();
    for (User* user : users) {
        if (user->getName().empty() && user->getUserId().empty()) continue;

        file << user->toFileFormat() << "\n";
    }

    file.close();
    return true;
}

// Load books from file
bool FileManager::loadBooksFromFile(Library& library) {
    ifstream file(booksFileName);
    if (!file.is_open()) {
        cout << "Aucun fichier de livres existant trouvé. Démarrage avec une bibliothèque vide.\n";
        return false;
    }

    string line;
    int count = 0;
    while (getline(file, line)) {
        if (line.empty()) continue; // ignore les lignes vides
            Book book;
            book.fromFileFormat(line);
                    if (book.getISBN().empty()) continue;
        if (library.findBookByISBN(book.getISBN())) continue;

            library.addBook(book);
            count++;
        
            
    }

    file.close();
    cout << "Chargé " << count << " livre(s) depuis le fichier.\n";
    return true;
}

// Load users from file
bool FileManager::loadUsersFromFile(Library& library) {
    ifstream file(usersFileName);
    if (!file.is_open()) {
        cout << "Aucun fichier d'utilisateurs existant trouvé. Démarrage sans utilisateurs enregistrés.\n";
        return false;
    }

    string line;
    int count = 0;
    while (getline(file, line)) {
        if (line.empty()) continue;
    if (line == "||" || line == "|") continue;
            User user;
            user.fromFileFormat(line);
            library.addUser(user);
            count++;
        }
    

    file.close();
    cout << "Chargé " << count << " utilisateur(s) depuis le fichier.\n";
    return true;
}

// Check if file exists
bool FileManager::fileExists(const string& filename) {
    ifstream file(filename);
    return file.good();
}

// Create backup
void FileManager::createBackup() {
     try {
        ifstream srcBooks(booksFileName, ios::binary);
        ofstream dstBooks(booksFileName + ".backup", ios::binary);
        dstBooks << srcBooks.rdbuf();

        ifstream srcUsers(usersFileName, ios::binary);
        ofstream dstUsers(usersFileName + ".backup", ios::binary);
        dstUsers << srcUsers.rdbuf();

        cout << "Fichiers de sauvegarde créés.\n";
    } catch (...) {
        cout << "Erreur : Impossible de créer la sauvegarde.\n";
    }
}
void FileManager::appendBorrowLog(const string& userId,
                                  const string& userName,
                                  const string& isbn,
                                  const string& title,
                                  const string& action)
{
    time_t now = time(nullptr);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&now));

    ofstream out(logsFileName, ios::app);
    if (!out.is_open()) {
        cout << "Erreur : impossible d'ouvrir " << logsFileName <<"en écriture.\n";
        return;
    }

    out << "[" << buffer << "] "
        << action
        << " | Utilisateur: " << userName
        << " (ID: " << userId << ")"
        << " | Livre: " << title
        << " (ISBN: " << isbn << ")"
        << "\n";

    out.close();
}