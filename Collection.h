#pragma once
#include "Book.h"
#include <iostream>
#include <string>
#include <vector>

class Collection
{
private:
	int ID;
	std::string name;
	std::vector<Book> bookList;
public:
	Collection();
	Collection(std::string, std::vector<Book> = {});
	Collection(const Collection&);
	~Collection();

	int getID() const;

	void setName(std::string);
	std::string getName() const;

	std::vector<Book>& getBookList();

	void addBook(Book&);
	void removeBook(int);

	Collection& operator=(const Collection&);
	bool operator==(const Collection&);
	bool operator!=(const Collection&);
};