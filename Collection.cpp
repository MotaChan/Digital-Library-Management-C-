#include "Collection.h"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

Collection::Collection() : ID(0), name("") , bookList({}) {}

Collection::Collection(string name, vector<Book> bookList)
{
	srand(static_cast<unsigned int>(time(0)));
	ID = rand() % ID_DIGITS;
	this->name = name;
	this->bookList = bookList;
}

Collection::Collection(const Collection& collection)
{
	ID = collection.ID;
	name = collection.name;
	for (int i = 0; i < collection.bookList.size(); i++) {
		bookList.push_back(collection.bookList[i]);
	}
}

Collection::~Collection(){}

int Collection::getID() const
{
	return ID;
}

void Collection::setName(string name)
{
	this->name = name;
}

std::string Collection::getName() const
{
	return name;
}

std::vector<Book>& Collection::getBookList()
{
	return bookList;
}

void Collection::addBook(Book& book) {
	bookList.push_back(book);
}

void Collection::removeBook(int bookPosition)
{
	if (bookList.size() == bookPosition) {
		bookList.pop_back();
		return;
	}
	for (int i = bookPosition; i < bookList.size() - 1; i++) {
		bookList[i] = bookList[i + 1];
	}
	bookList.pop_back();
}

Collection& Collection::operator=(const Collection& collection)
{
	if (this != &collection) {
		ID = collection.ID;
		name = collection.name;
		for (int i = 0; i < collection.bookList.size(); i++) {
			bookList.push_back(collection.bookList[i]);
		}
	}
	return *this;
}

bool Collection::operator==(const Collection& collection)
{
	if (ID != collection.ID) return false;
	if (name != collection.name) return false;
	if (bookList.size() != collection.bookList.size()) return false;
	for (int i = 0; i < bookList.size(); i++) {
		if (bookList[i] != collection.bookList[i]) return false;
	}
	return true;
}

bool Collection::operator!=(const Collection& collection)
{
	return !(* this == collection);
}
