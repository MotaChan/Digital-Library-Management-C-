#pragma once
#include <iostream>
#include <string>
#include "User.h"

class RegisteredUser : public User
{
private:
	std::string username;
	int ID;
	std::string password;
	std::string phoneNumber;
	std::string fullname;
public:
	RegisteredUser();
	RegisteredUser(std::string, std::string, std::string, std::string, accessibilityType);
	RegisteredUser(const RegisteredUser&);
	~RegisteredUser();
	
	void readBook(Book&);

	void setUsername(std::string);
	std::string getUsername() const;

	void setPassword(std::string);
	std::string getPassword() const;

	void setPhoneNumber(std::string);
	std::string getPhoneNumber() const;

	void setFullname(std::string);
	std::string getFullname() const;

	int getID() const;

	virtual void display() = 0;

	virtual void changeUsername() = 0;
	void changePassword();
	void changePhoneNumber();
	void changeFullname();

	int displayCollectionList();
	void readBookInCollection(int, int);
	virtual int displayBooksInCollection(int) = 0;

	int loginMenu();
	int userProfileMenu();
	int userEditProfileMenu();

	RegisteredUser& operator=(const RegisteredUser&);
};