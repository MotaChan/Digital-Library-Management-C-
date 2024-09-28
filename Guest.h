#pragma once
#include <iostream>
#include <string>
#include "Member.h"

class Guest : public User
{
private:
	int ID;
public:
	Guest(accessibilityType = GUEST);
	void readBook(Book&);
	bool registerMember();

	int mainMenu();
	int sampleCollectionMenu();
};