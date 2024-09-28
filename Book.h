#pragma once
#include <iostream>
#include <string>

const int ID_DIGITS = 1000000, DEFAULT_FREEPAGES = 5;

class Book
{
private:
	std::string title;
	std::string serialNumber;
	std::string authorName;
	int pagesCount;
	int freePages;
	std::string category;
	bool visibilityStatus;
	bool availabilityStatus;
	int ID;
public:
	Book();
	Book(std::string, std::string, std::string, int, std::string, int = DEFAULT_FREEPAGES, bool visibilityStatus = true, bool availabilityStatus = true);
	~Book();

	void setTitle(std::string);
	std::string getTitle() const;

	void setSerialNumber(std::string);
	std::string getSerialNumber() const;

	void setAuthorName(std::string);
	std::string getAuthorName() const;

	void setPagesCount(int);
	int getPagesCount() const;

	void setFreePages(int);
	int getFreePages() const;

	void setCategory(std::string);
	std::string getCategory() const;

	void setVisibilityStatus(bool);
	bool getVisibilityStatus() const;

	void setAvailabilityStatus(bool);
	bool getAvailabilityStatus() const;

	int getID() const;

	void display();

	bool operator!=(const Book&);
	bool operator==(const Book&);
};

