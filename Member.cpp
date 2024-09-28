#include "Member.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<Member> Member::memberList{};

int Member::getStartYear() const {
    return startYear;
}

int Member::getEndYear() const {
    return endYear;
}

Member::Member() : startYear(0), endYear(0), borrowList({}), subscribedCollectionList({}) {}

Member::Member(string username, string password, string phoneNumber, string fullname, accessibilityType accessibilityLevel, int startYear, int endYear, vector<Book> borrowList, vector<Collection> subscribedCollectionList) : RegisteredUser(username, password, phoneNumber, fullname, accessibilityLevel)
{
    this->startYear = startYear;
    this->endYear = endYear;
    this->borrowList = borrowList;
    this->subscribedCollectionList = subscribedCollectionList;
    this->subscribeCollection(0);
}

Member::Member(const Member& member) : RegisteredUser(member) {
    startYear = member.startYear;
    endYear = member.endYear;
    for (int i = 0; i < member.borrowList.size(); i++) {
        borrowList.push_back(member.borrowList[i]);
    }
    for (int i = 0; i < member.subscribedCollectionList.size(); i++) {
        subscribedCollectionList.push_back(member.subscribedCollectionList[i]);
    }
}

Member::~Member(){}

vector<Book>& Member::getBorrowList()
{
    return borrowList;
}

vector<Member>& Member::getMemberList()
{
    return memberList;
}

vector<Collection>& Member::getSubscribedCollectionList()
{
    return subscribedCollectionList;
}

Book* Member::searchBookByTitle()
{
    bool borrowedOrNot = false;
    vector<Book>& bookList = this->getBookList();
    cout << "Enter book's title: ";
    string title;
    getline(cin, title);
    for (int i = 0; i < borrowList.size(); i++) {
        if (title == borrowList[i].getTitle()) {
            borrowedOrNot = true;
            break;
        }
    }
    for (int i = 0; i < bookList.size(); i++) {
        if (bookList[i].getTitle() == title) {
            if (bookList[i].getVisibilityStatus() == false) { cerr << "Book not found" << endl; return nullptr; }
            if (bookList[i].getAvailabilityStatus() == false && !borrowedOrNot) { cerr << "Book borrowed" << endl; return nullptr; }
            return &bookList[i];
        }
    }
    cerr << "Book not found" << endl;
    return nullptr;
}

Book* Member::searchBookBySerial()
{
    bool borrowedOrNot = false;
    vector<Book>& bookList = this->getBookList();
    cout << "Enter book's serial number: ";
    string serialNumber;
    getline(cin, serialNumber);
    for (int i = 0; i < borrowList.size(); i++) {
        if (serialNumber == borrowList[i].getSerialNumber()) {
            borrowedOrNot = true;
            break;
        }
    }
    for (int i = 0; i < bookList.size(); i++) {
        if (bookList[i].getSerialNumber() == serialNumber) {
            if (bookList[i].getVisibilityStatus() == false) { cerr << "Book not found" << endl; return nullptr; }
            if (bookList[i].getAvailabilityStatus() == false && !borrowedOrNot) { cerr << "Book borrowed" << endl; return nullptr; }
            return &bookList[i];
        }
    }
    cerr << "Book not found" << endl;
    return nullptr;
}

void Member::addMember(Member& member)
{
    memberList.push_back(member);
}

Member* Member::login()
{
    string username, password;
    cout << "Enter your username: ";
    getline(cin, username);
    for (int i = 0; i < memberList.size(); i++) {
        if (memberList[i].getUsername() == username) {
            cout << "Enter your password: ";
            getline(cin, password);
            if (memberList[i].getPassword() == password) {
                cout << "Login successfully" << endl;
                return &memberList[i];
            }
            cout << "Wrong password" << endl;
            return nullptr;
        }
    }
    cout << "Username not found" << endl;
    return nullptr;
}

void Member::borrowBook(Book& book)
{
    borrowList.push_back(book);
    book.setAvailabilityStatus(false);
    cout << "Book borrowed successfully!" << endl;
}

void Member::borrowBookChosenFromAllCollections(int collectionPosition, int bookPosition)
{
    vector<Collection>& collectionList = this->getCollectionList();
    vector<Book>& bookList = collectionList[collectionPosition - 1].getBookList();
    this->borrowBook(bookList[bookPosition - 1]);
}

void Member::borrowBookChosenFromSubscribedCollections(int collectionPosition, int bookPosition)
{
    vector<Book>& bookList = subscribedCollectionList[collectionPosition - 1].getBookList();
    this->borrowBook(bookList[bookPosition - 1]);
}


void Member::returnBook(int bookPosition)
{
    if (bookPosition == borrowList.size()) borrowList.pop_back();
    else {
        for (int i = bookPosition; i < borrowList.size() - 1; i++) {
            borrowList[i] = borrowList[i + 1];
        }
        borrowList.pop_back();
    }
}

void Member::returnBook(Book& book)
{
    vector<Book>& bookList = this->getBookList();
    int bookInBookListPosition;
    for (int i = 0; i < bookList.size(); i++) {
        if (book == bookList[i]) bookInBookListPosition = i;
    }
    int bookInBorrowedListPosition;
    for (int i = 0; i < borrowList.size(); i++) {
        if (borrowList[i] == book) bookInBorrowedListPosition = i;
    }
    if (bookInBorrowedListPosition == borrowList.size()) borrowList.pop_back();
    else {
        for (int i = bookInBorrowedListPosition; i < borrowList.size() - 1; i++) {
            borrowList[i] = borrowList[i + 1];
        }
        borrowList.pop_back();
    }
    bookList[bookInBookListPosition].setAvailabilityStatus(true);
    cout << "Book returned successfully!" << endl;
}

void Member::returnBookChosenFromAllCollections(int collectionPosition, int bookPosition)
{
    vector<Collection>& collectionList = this->getCollectionList();
    vector<Book>& bookList = collectionList[collectionPosition - 1].getBookList();
    this->returnBook(bookList[bookPosition - 1]);
}

void Member::returnBookChosenFromSubscribedCollections(int collectionPosition, int bookPosition)
{
    vector<Book>& bookList = subscribedCollectionList[collectionPosition - 1].getBookList();
    this->returnBook(bookList[bookPosition - 1]);
}

void Member::subscribeCollection(int collectionPosition) {
    vector<Collection>& collectionList = this->getCollectionList();
    subscribedCollectionList.push_back(collectionList[collectionPosition]);
    cout << "Collection subscribed successfully!" << endl;
}

void Member::unsubscribeCollection(int collectionPosition) 
{
    if (collectionPosition == subscribedCollectionList.size()) subscribedCollectionList.pop_back();
    else {
        for (int i = collectionPosition; i < subscribedCollectionList.size() - 1; i++) {
            subscribedCollectionList[i] = subscribedCollectionList[i + 1];
        }
        subscribedCollectionList.pop_back();
    }
    cout << "Collection unsubscribed successfully!" << endl;
}

int Member::displaySubscribedCollectionList()
{
    cout << "-----Subscribed Collection-----" << endl;
    int count = 0;
    for (int i = 0; i < subscribedCollectionList.size(); i++) {
        cout << ++count << ". " << subscribedCollectionList[i].getName() << endl;
    }
    if (count == 0) cout << "You haven't subscribed to any collections" << endl;
    cout << ++count << ". Exit" << endl;
    return count;
}

int Member::displayBorrowList()
{
    int count = 0;
    cout << "-----Borrow List-----" << endl;
    for (int i = 0; i < borrowList.size(); i++) {
        if (borrowList[i].getVisibilityStatus() == false) {
            this->returnBook(i);
            i--;
        }
        else {
            cout << ++count << ". " << borrowList[i].getTitle() << endl;
        }
    }
    if (count == 0) cout << "No books in borrow list." << endl;
    cout << ++count << ". Exit" << endl;
    return count;
}

void Member::display()
{
    cout << "Username: " << this->getUsername() << endl;
    cout << "ID: " << this->getID() << endl;
    cout << "Phone Number: " << this->getPhoneNumber() << endl;
    cout << "Full name: " << this->getFullname() << endl;
    cout << "Start year: " << this->getStartYear() << endl;
    cout << "End year: " << this->getEndYear() << endl;
}

void Member::readAndBorrowBook(Book& book)
{
    int userOption;
    bool flag = true, borrowOrNot;
    while (flag) {
        borrowOrNot = this->readAndBorrowBookMenu(book);
        userOption = this->chooseOption(READ_AND_BORROW_BOOK_OPTIONS);
        switch (userOption) {
        case 1:
            book.display();
            this->readBook(book);
            break;
        case 2:
            if (borrowOrNot) this->borrowBook(book);
            else this->returnBook(book);
            break;
        case 3:
            flag = false;
            break;
        }
    }
}

void Member::readBookInBorrowList(int bookPosition)
{
    borrowList[bookPosition - 1].display();
    this->readBook(borrowList[bookPosition - 1]);
}

int Member::displayBooksInSubscribedCollection(int collectionPosition)
{
    vector<Book>& bookList = subscribedCollectionList[collectionPosition - 1].getBookList();
    cout << "-----" << subscribedCollectionList[collectionPosition - 1].getName() << "-----" << endl;
    int count = 0;
    for (int i = 0; i < bookList.size(); i++) {
        if (bookList[i].getVisibilityStatus() == false) {
            subscribedCollectionList[collectionPosition - 1].removeBook(i);
            i--;
        }
        else {
            cout << ++count << ". " << bookList[i].getTitle() << endl;
        }
    }
    if (count == 0) cerr << "There's no books in this collection" << endl;
    cout << ++count << ". Exit" << endl;
    return count;
}

void Member::readBookInSubscribedCollectionChosenFromAllCollections(int collectionPosition, int bookPosition)
{
    vector<Collection>& collectionList = this->getCollectionList();
    vector<Book>& bookList = collectionList[collectionPosition - 1].getBookList();
    bookList[bookPosition - 1].display();
    this->readBook(bookList[bookPosition - 1]);
}

void Member::readBookInSubscribedCollectionChosenFromSubscribedCollections(int collectionPosition, int bookPosition)
{
    vector<Book>& bookList = subscribedCollectionList[collectionPosition - 1].getBookList();
    bookList[bookPosition - 1].display();
    this->readBook(bookList[bookPosition - 1]);
}

int Member::displayBooksInCollection(int collectionPosition)
{
    vector<Collection>& collectionList = this->getCollectionList();
    int count = this->User::displayBooksInCollection(collectionList[collectionPosition]);
    cout << ++count << ". Exit" << endl;
    return count;
}

void Member::changeUsername()
{
    cout << "Current Username: " << this->getUsername() << endl;
    cout << "Enter new Username: ";
    string username;
    getline(cin, username);
    if (username == this->getUsername()) {
        cerr << "This is your current username!" << endl;
        return;
    }
    for (int i = 0; i < memberList.size(); i++) {
        if (memberList[i].getUsername() == username) {
            cerr << "Username existed" << endl;
            return;
        }
    }
    this->setUsername(username);
    cout << "Username changing successfully!" << endl;
}

int Member::mainMenu()
{
    cout << "-----Member Menu-----" << endl;
    cout << "1. Search Books" << endl;
    cout << "2. Borrow List" << endl;
    cout << "3. Collection List" << endl;
    cout << "4. Profile" << endl;
    cout << "5. Logout" << endl;

    vector<Book>& bookList = this->getBookList();
    bool removed = true;
    for (int i = 0; i < borrowList.size(); i++) {
        for (int k = 0; k < bookList.size(); k++) {
            if (borrowList[i].getID() == bookList[k].getID()) {
                removed = false;
                borrowList[i] = bookList[k];
                break;
            }
        }
        if (removed) {
            this->returnBook(i);
            i--;
        }
    }
    removed = true;
    vector<Collection>& collectionList = this->getCollectionList();
    for (int i = 0; i < subscribedCollectionList.size(); i++) {
        for (int k = 0; k < collectionList.size(); k++) {
            if (subscribedCollectionList[i].getID() == collectionList[k].getID()) {
                removed = false;
                subscribedCollectionList[i] = collectionList[k];
                break;
            }
        }
        if (removed) {
            this->unsubscribeCollection(i);
            i--;
        }
    }


    return 5;
}

bool Member::readAndBorrowBookMenu(Book& book)
{
    bool borrowOrNot;
    cout << "-----" << book.getTitle() << "-----" << endl;
    cout << "1. Read Book" << endl;
    if (book.getAvailabilityStatus() == true) { cout << "2. Borrow Book" << endl; borrowOrNot = true; }
    else { cout << "2. Return Book" << endl; borrowOrNot = false; }
    cout << "3. Exit" << endl;
    return borrowOrNot;
}

int Member::borrowedBookMenu(int bookPosition)
{
    cout << "-----" << borrowList[bookPosition - 1].getTitle() << "-----" << endl;
    cout << "1. Read Book" << endl;
    cout << "2. Return Book" << endl;
    cout << "3. Exit" << endl;
    return 3;
}

int Member::collectionMenu()
{
    cout << "-----Collection Menu-----" << endl;
    cout << "1. All Collections" << endl;
    cout << "2. Subscribed Collections" << endl;
    cout << "3. Exit" << endl;
    return 3;
}

bool Member::subscribedCollectionBookChosenFromAllCollectionsMenu(int collectionPosition, int bookPosition)
{
    bool borrowOrNot;
    vector<Collection>& collectionList = this->getCollectionList();
    vector<Book>& bookList = collectionList[collectionPosition - 1].getBookList();
    for (int i = 0; i < borrowList.size(); i++) {
        if (bookList[bookPosition - 1] == borrowList[i]) {
            cout << "-----" << bookList[bookPosition - 1].getTitle() << "-----" << endl;
            cout << "1. Read Book" << endl;
            cout << "2. Return Book" << endl; borrowOrNot = false;
            cout << "3. Exit" << endl;
            return borrowOrNot;
        }
    }
    if (bookList[bookPosition - 1].getAvailabilityStatus() == true) { 
        cout << "-----" << bookList[bookPosition - 1].getTitle() << "-----" << endl;
        cout << "1. Read Book" << endl;
        cout << "2. Borrow Book" << endl; borrowOrNot = true;
        cout << "3. Exit" << endl;
        return borrowOrNot;
    }
    else {
        cout << "This book is borrowed!" << endl;
        throw BookBorrowed();
    }
}

bool Member::subscribedCollectionBookChosenFromSubscribedCollectionsMenu(int collectionPosition, int bookPosition)
{
    bool borrowOrNot;
    vector<Book>& bookList = subscribedCollectionList[collectionPosition - 1].getBookList();
    for (int i = 0; i < borrowList.size(); i++) {
        if (bookList[bookPosition - 1] == borrowList[i]) {
            cout << "-----" << bookList[bookPosition - 1].getTitle() << "-----" << endl;
            cout << "1. Read Book" << endl;
            cout << "2. Return Book" << endl; borrowOrNot = false;
            cout << "3. Exit" << endl;
            return borrowOrNot;
        }
    }
    if (bookList[bookPosition - 1].getAvailabilityStatus() == true) {
        cout << "-----" << bookList[bookPosition - 1].getTitle() << "-----" << endl;
        cout << "1. Read Book" << endl;
        cout << "2. Borrow Book" << endl; borrowOrNot = true;
        cout << "3. Exit" << endl;
        return borrowOrNot;
    }
    else {
        cout << "This book is borrowed!" << endl;
        throw BookBorrowed();
    }
}

int Member::chosenFromAllCollectionsMenu(int collectionPosition)
{
    bool subOrNot = false;
    int userOption = 0;
    vector<Collection>& collectionList = this->getCollectionList();
    for (int i = 0; i < subscribedCollectionList.size(); i++) {
        if (subscribedCollectionList[i] == collectionList[collectionPosition - 1]) subOrNot = true;
    }
    if (subOrNot) {
        return this->displayBooksInCollection(collectionPosition - 1);
    }
    else {
        cout << "You have to subscribe this Collection to see all Books" << endl;
        cout << "1. Subscribe Collection" << endl;
        cout << "2. Exit" << endl;
        userOption = this->chooseOption(2);
        switch (userOption) {
        case 1:
            this->subscribeCollection(collectionPosition - 1);
            return this->displayBooksInCollection(collectionPosition - 1);
        case 2:
            return -1;
        }
    }
    return 0;
}

int Member::unsubOrShowBooksMenu(int collectionPosition)
{
    cout << "-----" << subscribedCollectionList[collectionPosition - 1].getName() << "-----" << endl;
    cout << "1. Unsubscribe" << endl;
    cout << "2. Show Books" << endl;
    cout << "3. Exit" << endl;
    return 3;
}

Member& Member::operator=(const Member& member) {
    if (this != &member) {
        RegisteredUser::operator=(member);
        startYear = member.startYear;
        endYear = member.endYear;
        for (int i = 0; i < member.borrowList.size(); i++) {
            borrowList.push_back(member.borrowList[i]);
        }
        for (int i = 0; i < member.subscribedCollectionList.size(); i++) {
            subscribedCollectionList.push_back(member.subscribedCollectionList[i]);
        }
    }
    return *this;
}

bool Member::operator==(const Member& member) {
    if (startYear != member.startYear) return false;
    if (endYear != member.endYear) return false;
    if (borrowList.size() != member.borrowList.size()) return false;
    for (int i = 0; i < borrowList.size(); i++) {
        if (borrowList[i] != member.borrowList[i]) return false;
    }
    if (subscribedCollectionList.size() != member.subscribedCollectionList.size()) return false;
    for (int i = 0; i < subscribedCollectionList.size(); i++) {
        if (subscribedCollectionList[i] != member.subscribedCollectionList[i]) return false;
    }
    return true;
}