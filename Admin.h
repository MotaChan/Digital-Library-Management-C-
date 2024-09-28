#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "RegisteredUser.h"

class Admin : public RegisteredUser
{
private:
	static std::vector<Admin> adminList;
public:
	Admin();
	Admin(std::string, std::string, std::string, std::string, accessibilityType = ADMIN);
	Admin(const Admin&);
	~Admin();

	void addBook();
	void hideBook(Book*);
	void showBook(int);

	void createCollection();
	void removeCollection(int);

	void addAdmin(Admin&);
	void createAdmin();

	void addBookInCollection(int, Book&);
	void removeBookInCollection(int, int);

	void editCollection(int);

	Book* searchBookByTitle();
	Book* searchBookBySerial();

	Admin* login();

	void display();

	void manageBook(Book*);

	int displayBooksInCollection(int);

	void changeUsername();

	int mainMenu();
	int manageBookMenu();
	int editBookMenu();
	int displayHiddenBookList();
	int manageCollectionMenu(int);
	int addBookInCollectionMenu();
	int manageBookInCollectionMenu(int, int);
	Admin& operator=(const Admin&);
};