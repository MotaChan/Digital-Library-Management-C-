#include "Book.h"
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

Book::Book() : title(""), serialNumber(""), authorName(""), pagesCount(0), freePages(0), category(""), visibilityStatus(true), availabilityStatus(true), ID(0) {}

Book::Book(string title, string serialNumber, string authorName, int pagesCount, string category, int freePages, bool visibilityStatus, bool availabilityStatus)
{
	srand(static_cast<unsigned int>(time(0)));
	this->title = title;
	this->serialNumber = serialNumber;
	this->authorName = authorName;
	this->pagesCount = pagesCount;
	this->freePages = freePages;
	this->category = category;
	this->visibilityStatus = visibilityStatus;
	this->availabilityStatus = availabilityStatus;
	ID = rand() % ID_DIGITS;
}

Book::~Book(){}

void Book::setTitle(string title)
{
	this->title = title;
}

std::string Book::getTitle() const
{
	return title;
}

void Book::setSerialNumber(string serialNumber)
{
	this->serialNumber = serialNumber;
}

std::string Book::getSerialNumber() const
{
	return serialNumber;
}

void Book::setAuthorName(std::string authorName)
{
	this->authorName = authorName;
}

std::string Book::getAuthorName() const
{
	return authorName;
}

void Book::setPagesCount(int pagesCount)
{
	this->pagesCount = pagesCount;
}

int Book::getPagesCount() const
{
	return pagesCount;
}

void Book::setFreePages(int freePages)
{
	this->freePages = freePages;
}

int Book::getFreePages() const
{
	return freePages;
}

void Book::setCategory(std::string category)
{
	this->category = category;
}

std::string Book::getCategory() const
{
	return category;
}

void Book::setVisibilityStatus(bool visibilityStatus)
{
	this->visibilityStatus = visibilityStatus;
}

bool Book::getVisibilityStatus() const
{
	return visibilityStatus;
}

void Book::setAvailabilityStatus(bool availabilityStatus)
{
	this->availabilityStatus = availabilityStatus;
}

bool Book::getAvailabilityStatus() const
{
	return availabilityStatus;
}

int Book::getID() const
{
	return ID;
}

void Book::display()
{
	cout << "Title: " << getTitle() << endl;
	cout << "Serial Number: " << getSerialNumber() << endl;
	cout << "Author name: " << getAuthorName() << endl;
	cout << "Total pages: " << getPagesCount() << endl;
	cout << "Category: " << getCategory() << endl;
}

bool Book::operator!=(const Book& book) {
	return(!(title == book.title && serialNumber == book.serialNumber && authorName == book.authorName && pagesCount == book.pagesCount && freePages == book.freePages && category == book.category && visibilityStatus == book.visibilityStatus && availabilityStatus == book.availabilityStatus && ID == book.ID));
}

bool Book::operator==(const Book& book)
{
	return(title == book.title && serialNumber == book.serialNumber && authorName == book.authorName && pagesCount == book.pagesCount && freePages == book.freePages && category == book.category && visibilityStatus == book.visibilityStatus && availabilityStatus == book.availabilityStatus && ID == book.ID);
}
