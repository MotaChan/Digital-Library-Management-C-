#pragma once
#include "RegisteredUser.h"
#include <iostream>
#include <string>
#include <vector>

const int CURRENT_YEAR = 2023, NEXT_YEAR = 2024, READ_AND_BORROW_BOOK_OPTIONS = 3;

class Member : public RegisteredUser
{
private:
	int startYear;
	int endYear;
	std::vector<Book> borrowList;
	std::vector<Collection> subscribedCollectionList;
	static std::vector<Member> memberList;
protected:
	int getStartYear() const;

	int getEndYear() const;
public:
	class BookBorrowed{};
	Member();
	Member(std::string, std::string, std::string, std::string, accessibilityType = MEMBER, int = CURRENT_YEAR, int = NEXT_YEAR, std::vector<Book> = {}, std::vector<Collection> = {});
	Member(const Member&);
	~Member();

	std::vector<Book>& getBorrowList();

	static std::vector<Member>& getMemberList();

	std::vector<Collection>& getSubscribedCollectionList();

	Book* searchBookByTitle();
	Book* searchBookBySerial();

	void addMember(Member&);

	Member* login();

	void borrowBook(Book&);
	void borrowBookChosenFromAllCollections(int, int);
	void borrowBookChosenFromSubscribedCollections(int, int);

	void returnBook(int);
	void returnBook(Book&);
	void returnBookChosenFromAllCollections(int, int);
	void returnBookChosenFromSubscribedCollections(int, int);

	void subscribeCollection(int);
	void unsubscribeCollection(int);

	int displaySubscribedCollectionList();

	int displayBorrowList();

	void display();

	void readAndBorrowBook(Book&);

	void readBookInBorrowList(int);

	int displayBooksInSubscribedCollection(int);

	void readBookInSubscribedCollectionChosenFromAllCollections(int, int);
	void readBookInSubscribedCollectionChosenFromSubscribedCollections(int, int);

	int displayBooksInCollection(int);

	void changeUsername();

	int mainMenu();
	bool readAndBorrowBookMenu(Book&);
	int borrowedBookMenu(int);
	int collectionMenu();
	bool subscribedCollectionBookChosenFromAllCollectionsMenu(int, int);
	bool subscribedCollectionBookChosenFromSubscribedCollectionsMenu(int, int);
	int chosenFromAllCollectionsMenu(int);
	int unsubOrShowBooksMenu(int);

	Member& operator=(const Member&);
	bool operator==(const Member&);
};

