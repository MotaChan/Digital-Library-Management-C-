#include "User.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<Book> User::bookList{};
vector<Collection> User::collectionList{};

accessibilityType User::getAccesscibilityLevel() const
{
	return accessibilityLevel;
}

void User::addBook(Book& book)
{
	bookList.push_back(book);
}

void User::removeBook(Book* book)
{
	int bookPosition;
	for (int i = 0; i < collectionList.size(); i++) {
		vector<Book>& bookList = collectionList[i].getBookList();
		for (int k = 0; k < bookList.size(); k++) {
			if (bookList[k] == *book) {
				collectionList[i].removeBook(k);
				break;
			}
		}
	}
	for (int i = 0; i < bookList.size(); i++) {
		if (bookList[i] == *book) bookPosition = i;
	}
	if (bookPosition == bookList.size()) bookList.pop_back();
	else {
		for (int i = bookPosition; i < bookList.size() - 1; i++) {
			bookList[i] = bookList[i + 1];
		}
		bookList.pop_back();
	}
	cout << "Book removed successfully" << endl;
}

vector<Book>& User::getBookList()
{
	return bookList;
}

void User::addCollection(Collection& collection)
{
	collectionList.push_back(collection);
}

void User::removeCollection(int collectionPosition)
{
	if (collectionPosition == collectionList.size()) collectionList.pop_back();
	else {
		for (int i = collectionPosition; i < collectionList.size() - 1; i++) {
			collectionList[i] = collectionList[i + 1];
		}
		collectionList.pop_back();
	}
}

vector<Collection>& User::getCollectionList()
{
	return collectionList;
}

User::User(accessibilityType accessibilityLevel)
{
	this->accessibilityLevel = accessibilityLevel;
}

User::User(const User& user)
{
	accessibilityLevel = user.accessibilityLevel;
}

User::~User() {}

Book* User::searchBookByTitle()
{
	cout << "Enter book's title: ";
	string title;
	getline(cin, title);
	for (int i = 0; i < bookList.size(); i++) {
		if (bookList[i].getTitle() == title) {
			if (bookList[i].getVisibilityStatus() == false) { cerr << "Book not found" << endl; return nullptr; }
			if (bookList[i].getAvailabilityStatus() == false) { cerr << "Book borrowed" << endl; return nullptr; }
			return &bookList[i];
		}
	}
	cerr << "Book not found" << endl;
	return nullptr;
}

Book* User::searchBookBySerial()
{
	cout << "Enter book's serial: ";
	string serialNumber;
	getline(cin, serialNumber);
	for (int i = 0; i < bookList.size(); i++) {
		if (bookList[i].getSerialNumber() == serialNumber) {
			if (bookList[i].getVisibilityStatus() == false) { cerr << "Book not found" << endl; return nullptr; }
			if (bookList[i].getAvailabilityStatus() == false) { cerr << "Book borrowed" << endl; return nullptr; }
			return &bookList[i];
		}
	}
	cerr << "Book not found" << endl;
	return nullptr;
}

Collection* User::getCollection(int collectionPosition)
{
	return &collectionList[collectionPosition];
}

Book* User::getBook(Collection& collection, int bookPosition)
{
	for (int i = 0; i < collectionList.size(); i++) {
		if (collection == collectionList[i]) return &collectionList[i].getBookList()[bookPosition];
	}
}

int User::displayBooksInCollection(Collection& collection)
{
	vector<Book>& bookList = collection.getBookList();
	cout << "-----" << collection.getName() << " Collection-----" << endl;
	int count = 0;
	for (int i = 0; i < bookList.size(); i++) {
		if (bookList[i].getVisibilityStatus() == false) {
			collection.removeBook(i);
			i--;
		}
		else {
			cout << ++count << ". " << bookList[i].getTitle() << endl;
		}
	}
	if (bookList.size() == 0) cout << "No books in this collection" << endl;
	return count;
}

int User::chooseOption(int optionNum)
{
	string userInput;
	bool flag;
	do {
		flag = false;
		cout << "Your option: ";
		getline(cin, userInput);
		if (userInput[0] == 48 || userInput == "") { flag = true; }
		else {
			for (int i = 0; i < userInput.length(); i++) {
				if (userInput[i] < 48 || userInput[i] > 57) { flag = true; break; }
			}
		}
	} while (flag || stoi(userInput) > optionNum);
	return stoi(userInput);
}

int User::searchBooksMenu()
{
	cout << "-----Search Books Menu-----" << endl;
	cout << "1. Search Books by Title" << endl;
	cout << "2. Search Books by Serial Number" << endl;
	cout << "3. Exit" << endl;
	return 3;
}

User& User::operator=(const User& user)
{
	if (this != &user) {
		accessibilityLevel = user.accessibilityLevel;
	}
	return *this;
}
