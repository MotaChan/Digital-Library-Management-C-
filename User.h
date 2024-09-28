#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Collection.h"

enum accessibilityType { GUEST, MEMBER, ADMIN };

class User
{
private:
	static std::vector<Book> bookList;
	static std::vector<Collection> collectionList;

	accessibilityType accessibilityLevel;
protected:
	accessibilityType getAccesscibilityLevel() const;

	void addBook(Book&);
	void removeBook(Book*);
	static std::vector<Book>& getBookList();

	void addCollection(Collection&);
	void removeCollection(int);
	static std::vector<Collection>& getCollectionList();
public:
	User(accessibilityType = GUEST);
	User(const User&);
	~User();
	virtual void readBook(Book&) = 0;

	virtual Book* searchBookByTitle();
	virtual Book* searchBookBySerial();

	Collection* getCollection(int);
	Book* getBook(Collection&, int);

	int displayBooksInCollection(Collection&);

	int chooseOption(int);

	int searchBooksMenu();
	User& operator=(const User&);
};

