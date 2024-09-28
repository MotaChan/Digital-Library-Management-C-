#include "Admin.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<Admin> Admin::adminList{};

Admin::Admin() {}

Admin::Admin(string username, string password, string phoneNumber, string fullname, accessibilityType accessibilityLevel) : RegisteredUser(username, password, phoneNumber, fullname, accessibilityLevel){}

Admin::Admin(const Admin& admin) : RegisteredUser(admin){}

Admin::~Admin() {}

void Admin::addBook() {
    string title, serialNumber, authorName, category;
    int pagesCount;
    vector<Book>& bookList = this->getBookList();
    cout << "Enter book's title: ";
    getline(cin, title);
    for (int i = 0; i < bookList.size(); i++) {
        if (bookList[i].getTitle() == title) {
            cerr << "Title existed" << endl;
            return;
        }
    }
    cout << "Enter book's Serial Number: ";
    getline(cin, serialNumber);
    for (int i = 0; i < bookList.size(); i++) {
        if (bookList[i].getSerialNumber() == serialNumber) {
            cerr << "Serial Number existed" << endl;
            return;
        }
    }
    cout << "Enter book's Author's name: ";
    getline(cin, authorName);
    cout << "Enter book's Category: ";
    getline(cin, category);
    cout << "Enter number of pages: ";
    cin >> pagesCount;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    Book book = Book(title, serialNumber, authorName, pagesCount, category);
    this->User::addBook(book);
    cout << "Book added successfully!" << endl;
}

void Admin::hideBook(Book* book)
{
    if (book->getVisibilityStatus() == false) {
        cerr << "This book is already hidden" << endl;
        return;
    }
    book->setVisibilityStatus(false);
    cout << "Book hidden successfully!" << endl;
}

void Admin::showBook(int bookPosition)
{
    int count = 0;
    vector<Book>& bookList = this->getBookList();
    for (int i = 0; i < bookList.size(); i++) {
        if (bookList[i].getVisibilityStatus() == false) {
            count++;
            if (count == bookPosition) {
                bookList[i].setVisibilityStatus(true);
                cout << "Book showed successfully!" << endl;
                break;
            }
        }
    }
}

void Admin::createCollection() {
    vector<Collection>& collectionList = this->getCollectionList();
    cout << "Enter collection's name: ";
    string name;
    getline(cin, name);
    for (int i = 0; i < collectionList.size(); i++) {
        if (collectionList[i].getName() == name) {
            cerr << "Name existed" << endl;
            return;
        }
    }
    Collection collection = Collection(name);
    this->addCollection(collection);
    cout << "Collection added successfully!" << endl;
}

void Admin::removeCollection(int collectionPosition)
{
    this->User::removeCollection(collectionPosition - 1);
    cout << "Collection Removed successfully!" << endl;
}

void Admin::addAdmin(Admin& admin)
{
    adminList.push_back(admin);
}

void Admin::createAdmin()
{
    string username, password, phoneNumber, fullname;
    cout << "Enter your username: ";
    getline(cin, username);
    for (int i = 0; i < adminList.size(); i++) {
        if (adminList[i].getUsername() == username) {
            cerr << "Username existed" << endl;
            return;
        }
    }
    cout << "Enter your password: ";
    getline(cin, password);
    cout << "Enter your phone number: ";
    getline(cin, phoneNumber);
    cout << "Enter your fullname: ";
    getline(cin, fullname);
    Admin admin = Admin(username, password, phoneNumber, fullname);
    adminList.push_back(admin);
    cout << "Create admin successfully" << endl;
}

void Admin::addBookInCollection(int collectionPosition, Book& book)
{
    vector<Collection>& collectionList = this->getCollectionList();
    vector<Book>& bookList = collectionList[collectionPosition - 1].getBookList();
    for (int i = 0; i < bookList.size(); i++) {
        if (bookList[i] == book) {
            cerr << "This Book is already in this Collection" << endl;
            return;
        }
    }
    collectionList[collectionPosition - 1].addBook(book);
    cout << "Book added successfully!" << endl;
}

void Admin::removeBookInCollection(int collectionPosition, int bookPosition)
{
    vector<Collection>& collectionList = this->getCollectionList();
    vector<Book>& bookList = collectionList[collectionPosition - 1].getBookList();
    collectionList[collectionPosition - 1].removeBook(bookPosition - 1);
    cout << "Book removed successfully!" << endl;
}

void Admin::editCollection(int collectionPosition)
{
    vector<Collection>& collectionList = this->getCollectionList();
    cout << "Current Collection's name: " << collectionList[collectionPosition - 1].getName() << endl;
    cout << "Enter collection's new name: ";
    string name;
    getline(cin, name);
    collectionList[collectionPosition - 1].setName(name);
    cout << "Changing name successfully!" << endl;
}

Book* Admin::searchBookByTitle()
{
    vector<Book>& bookList = this->getBookList();
    cout << "Enter book's title: ";
    string title;
    getline(cin, title);
    for (int i = 0; i < bookList.size(); i++) {
        if (bookList[i].getTitle() == title) {
            return &bookList[i];
        }
    }
    cerr << "Book not found" << endl;
    return nullptr;
}
Book* Admin::searchBookBySerial()
{
    vector<Book>& bookList = this->getBookList();
    cout << "Enter book's serial number: ";
    string serialNumber;
    getline(cin, serialNumber);
    for (int i = 0; i < bookList.size(); i++) {
        if (bookList[i].getSerialNumber() == serialNumber) {
            return &bookList[i];
        }
    }
    cerr << "Book not found" << endl;
    return nullptr;
}


Admin* Admin::login()
{
    string username, password;
    cout << "Enter your username: ";
    getline(cin, username);
    for (int i = 0; i < adminList.size(); i++) {
        if (adminList[i].getUsername() == username) {
            cout << "Enter your password: ";
            getline(cin, password);
            if (adminList[i].getPassword() == password) return &adminList[i];
            cout << "Wrong password" << endl;
            return nullptr;
        }
    }
    cout << "Username not found" << endl;
    return nullptr;
}

void Admin::display()
{
    cout << "-----Your Profile-----" << endl;
    cout << "Username: " << this->getUsername() << endl;
    cout << "ID: " << this->getID() << endl;
    cout << "Phone number: " << this->getPhoneNumber() << endl;
    cout << "Full name: " << this->getFullname() << endl;
}

void Admin::manageBook(Book* book)
{
    string title, serialNumber, authorName, category;
    int pagesCount, freePages;
    int userOption;
    bool flag = true;
    while (flag) {
        book->display();
        userOption = this->chooseOption(this->manageBookMenu());
        switch (userOption) {
        case 1:
            this->removeBook(book);
            flag = false;
            break;
        case 2:
            this->hideBook(book);
            break;
        case 3:
            flag = true;
            while (flag) {
                userOption = this->chooseOption(this->editBookMenu());
                switch (userOption) {
                case 1:
                    cout << "Current Title: " << book->getTitle() << endl;
                    cout << "Enter new Title: ";
                    getline(cin, title);
                    book->setTitle(title);
                    cout << "Title changing successfully!" << endl;
                    break;
                case 2:
                    cout << "Current Serial Number: " << book->getSerialNumber() << endl;
                    cout << "Enter new Serial Number: ";
                    getline(cin, serialNumber);
                    book->setSerialNumber(serialNumber);
                    cout << "Serial Number changing successfully!" << endl;
                    break;
                case 3:
                    cout << "Author's current name: " << book->getAuthorName() << endl;
                    cout << "Enter new name: ";
                    getline(cin, authorName);
                    book->setAuthorName(authorName);
                    cout << "Author's name changing successfully!" << endl;
                    break;
                case 4:
                    cout << "Current Category: " << book->getCategory() << endl;
                    cout << "Enter new Category: ";
                    getline(cin, category);
                    book->setCategory(category);
                    cout << "Category changing successfully!" << endl;
                    break;
                case 5:
                    cout << "Current Total pages: " << book->getPagesCount() << endl;
                    cout << "Enter new Total pages: ";
                    cin >> pagesCount;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    book->setPagesCount(pagesCount);
                    cout << "Total pages changing successfully!" << endl;
                    break;
                case 6:
                    cout << "Current Free pages: " << book->getFreePages() << endl;
                    cout << "Enter new Free pages: ";
                    cin >> freePages;
                    book->setFreePages(freePages);
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Free pages changing successfully!" << endl;
                    break;
                case 7:
                    flag = false;
                    break;
                }
            }
            break;
        case 4:
            this->readBook(*book);
            break;
        case 5:
            flag = false;
            break;
        }
    }
}

int Admin::displayBooksInCollection(int collectionPosition)
{
    vector<Collection>& collection = this->getCollectionList();
    int count = this->User::displayBooksInCollection(collection[collectionPosition - 1]);
    cout << ++count << ". Add Book" << endl;
    cout << ++count << ". Exit" << endl;
    return count;
}

void Admin::changeUsername()
{
    cout << "Current Username: " << this->getUsername() << endl;
    cout << "Enter new Username: ";
    string username;
    getline(cin, username);
    if (username == this->getUsername()) {
        cerr << "This is your current username!" << endl;
        return;
    }
    for (int i = 0; i < adminList.size(); i++) {
        if (adminList[i].getUsername() == username) {
            cerr << "Name existed" << endl;
            return;
        }
    }
    this->setUsername(username);
    cout << "Username changing successfully!" << endl;
}

int Admin::mainMenu()
{
    cout << "-----Admin Menu-----" << endl;
    cout << "1. Create Admin" << endl;
    cout << "2. Search Books" << endl;
    cout << "3. Hidden Book List" << endl;
    cout << "4. Add Book" << endl;
    cout << "5. Add Collection" << endl;
    cout << "6. Collection List" << endl;
    cout << "7. Profile" << endl;
    cout << "8. Logout" << endl;
    return 8;
}

int Admin::manageBookMenu()
{
    cout << "-----Manage Book Menu-----" << endl;
    cout << "1. Remove Book" << endl;
    cout << "2. Hide Book" << endl;
    cout << "3. Edit Book" << endl;
    cout << "4. Read Book" << endl;
    cout << "5. Exit" << endl;
    return 5;
}

int Admin::editBookMenu()
{
    cout << "-----Edit Book Menu-----" << endl;
    cout << "1. Change Title" << endl;
    cout << "2. Change Serial Number" << endl;
    cout << "3. Change Author's name" << endl;
    cout << "4. Change Category" << endl;
    cout << "5. Change Total Pages" << endl;
    cout << "6. Change Free Pages" << endl;
    cout << "7. Exit" << endl;
    return 7;
}

int Admin::displayHiddenBookList()
{
    int count = 0;
    vector<Book>& bookList = this->getBookList();
    cout << "-----Hidden Book List-----" << endl;
    for (int i = 0; i < bookList.size(); i++) {
        if (bookList[i].getVisibilityStatus() == false) {
            cout << ++count << ". " << bookList[i].getTitle() << endl;
        }
    }
    if (count == 0) {
        cout << "No books are hidden." << endl;
    }
    cout << ++count << ". Exit" << endl;
    if (count != 1) cout << "- Choose which book to show -" << endl;
    return count;
}

int Admin::manageCollectionMenu(int collectionPosition)
{
    vector<Collection>& collectionList = this->getCollectionList();
    cout << "-----" << collectionList[collectionPosition - 1].getName() << " Collection Menu----- " << endl;
    cout << "1. Remove this Collection" << endl;
    cout << "2. Change Collection's name" << endl;
    cout << "3. Show Collection's Books" << endl;
    cout << "4. Exit" << endl;
    return 4;
}

int Admin::addBookInCollectionMenu()
{
    cout << "-----Add Book Menu-----" << endl;
    cout << "1. Add Book by Title" << endl;
    cout << "2. Add Book by Serial Number" << endl;
    cout << "3. Exit" << endl;
    return 3;
}

int Admin::manageBookInCollectionMenu(int collectionPosition, int bookPosition)
{
    vector<Collection>& collectionList = this->getCollectionList();
    vector<Book>& bookList = collectionList[collectionPosition - 1].getBookList();
    cout << "-----" << bookList[bookPosition - 1].getTitle() << "-----" << endl;
    cout << "1. Remove this Book from this Collection" << endl;
    cout << "2. Read Book" << endl;
    cout << "3. Exit" << endl;
    return 3;
}

Admin& Admin::operator=(const Admin& admin)
{
    if (this != &admin) {
        RegisteredUser::operator=(admin);
    }
    return *this;
}
