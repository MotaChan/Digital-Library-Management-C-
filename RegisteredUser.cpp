#include "RegisteredUser.h"
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

RegisteredUser::RegisteredUser() : username(""), ID(0), password(""), phoneNumber(""), fullname("") {}

RegisteredUser::RegisteredUser(std::string username, std::string password, std::string phoneNumber, std::string fullname, accessibilityType accessibilityLevel) : User(accessibilityLevel)
{
	srand(static_cast<unsigned int>(time(0)));
	this->username = username;
	this->ID = rand() % ID_DIGITS;
	this->password = password;
	this->phoneNumber = phoneNumber;
	this->fullname = fullname;
}

RegisteredUser::RegisteredUser(const RegisteredUser& registeredUser) : User(registeredUser)
{
	username = registeredUser.username;
	password = registeredUser.password;
	phoneNumber = registeredUser.phoneNumber;
	fullname = registeredUser.fullname;
	ID = registeredUser.ID;
}

RegisteredUser::~RegisteredUser()
{
	User::~User();
}

void RegisteredUser::setUsername(std::string username)
{
	this->username = username;
}

std::string RegisteredUser::getUsername() const
{
	return username;
}

int RegisteredUser::getID() const
{
	return ID;
}

void RegisteredUser::changePassword()
{
	cout << "Current Password: " << this->getPassword() << endl;
	cout << "Enter new Password: ";
	string password;
	getline(cin, password);
	if (password == this->getPassword()) {
		cerr << "This is your current password!" << endl;
		return;
	}
	this->setPassword(password);
	cout << "Password changing successfully!" << endl;
}

void RegisteredUser::changePhoneNumber()
{
	cout << "Current Phone Number: " << this->getPhoneNumber() << endl;
	cout << "Enter new Phone Number: ";
	string phoneNumber;
	getline(cin, phoneNumber);
	if (phoneNumber == this->getPhoneNumber()) {
		cerr << "This is your current phone number!" << endl;
		return;
	}
	this->setPhoneNumber(phoneNumber);
	cout << "Phone Number changing successfully!" << endl;
}

void RegisteredUser::changeFullname()
{
	cout << "Current Fullname: " << this->getFullname() << endl;
	cout << "Enter new Fullname: ";
	string fullname;
	getline(cin, fullname);
	if (fullname == this->getFullname()) {
		cerr << "This is your current fullname!" << endl;
		return;
	}
	this->setFullname(fullname);
	cout << "Fullname changing successfully!" << endl;
}

int RegisteredUser::displayCollectionList()
{
	vector<Collection> collectionList = this->getCollectionList();
	cout << "-----Collection List-----" << endl;
	for (int i = 0; i < collectionList.size(); i++) {
		cout << i + 1 << ". " << collectionList[i].getName() << endl;
	}
	cout << collectionList.size() + 1 << ". Exit" << endl;
	return collectionList.size() + 1;
}

void RegisteredUser::readBookInCollection(int collectionPosition, int bookPosition)
{
	vector<Collection> collectionList = this->getCollectionList();
	vector<Book> bookList = collectionList[collectionPosition - 1].getBookList();
	this->readBook(bookList[bookPosition - 1]);
}

int RegisteredUser::loginMenu()
{
	cout << "-----Login Menu-----" << endl;
	cout << "1. Login as Admin" << endl;
	cout << "2. Login as Member" << endl;
	cout << "3. Exit" << endl;
	return 3;
}
int RegisteredUser::userProfileMenu()
{
	cout << "-----Profile Menu-----" << endl;
	cout << "1. Display Profile" << endl;
	cout << "2. Edit Profile" << endl;
	cout << "3. Exit" << endl;
	return 3;
}

int RegisteredUser::userEditProfileMenu()
{
	cout << "-----Edit Profile Menu-----" << endl;
	cout << "1. Change Username" << endl;
	cout << "2. Change Password" << endl;
	cout << "3. Change Phone Number" << endl;
	cout << "4. Change Fullname" << endl;
	cout << "5. Exit" << endl;
	return 5;
}

RegisteredUser& RegisteredUser::operator=(const RegisteredUser& registeredUser)
{
	if (this != &registeredUser) {
		User::operator=(registeredUser);
		ID = registeredUser.ID;
		username = registeredUser.username;
		password = registeredUser.password;
		phoneNumber = registeredUser.phoneNumber;
		fullname = registeredUser.fullname;
	}
	return *this;
}

void RegisteredUser::setPassword(std::string password)
{
	this->password = password;
}

std::string RegisteredUser::getPassword() const
{
	return password;
}

void RegisteredUser::setPhoneNumber(std::string phoneNumber)
{
	this->phoneNumber = phoneNumber;
}

std::string RegisteredUser::getPhoneNumber() const
{
	return phoneNumber;
}

void RegisteredUser::setFullname(std::string fullName)
{
	this->fullname = fullName;
}

std::string RegisteredUser::getFullname() const
{
	return fullname;
}

void RegisteredUser::readBook(Book& book)
{
	int userOption;
	for (int i = 0; i < book.getPagesCount(); i++) {
		if (i == 0) {
			cout << "---PAGE " << i + 1 << "---" << endl;
			cout << "You are reading page " << i + 1 << endl;
			cout << "1. Next page" << endl;
			cout << "2. Exit" << endl;
			userOption = this->chooseOption(2);
			switch (userOption) {
			case 1:
				break;
			case 2:
				return;
			}
		}
		else if (i == book.getPagesCount() - 1) {
			cout << "---PAGE " << i + 1 << "---" << endl;
			cout << "You are reading page " << i + 1 << endl;
			cout << "-----THE END-----" << endl;
			cout << "1. Previous page" << endl;
			cout << "2. Exit" << endl;
			userOption = this->chooseOption(2);
			switch (userOption) {
			case 1:
				i -= 2;
				break;
			case 2:
				return;
			}
		}
		else {
			cout << "---PAGE " << i + 1 << "---" << endl;
			cout << "You are reading page " << i + 1 << endl;
			cout << "1. Next page" << endl;
			cout << "2. Previous page" << endl;
			cout << "3. Exit" << endl;
			userOption = this->chooseOption(3);
			switch (userOption) {
			case 1:
				break;
			case 2:
				i -= 2;
				break;
			case 3:
				return;
			}
		}
	}
}