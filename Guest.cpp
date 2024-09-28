#include "Guest.h"
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

Guest::Guest(accessibilityType accessibilityLevel) : User(accessibilityLevel)
{
	srand(static_cast<unsigned int>(time(0)));
	ID = rand() % ID_DIGITS;
}

void Guest::readBook(Book& book)
{
	int userOption;
	for (int i = 0; i < book.getFreePages(); i++) {
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
		else if (i == book.getFreePages() - 1) {
			cout << "---PAGE " << i + 1 << "---" << endl;
			cout << "You are reading page " << i + 1 << endl;
			cout << "Register to read full book" << endl;
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

bool Guest::registerMember()
{
	Member member;
	vector<Member>& memberList = member.getMemberList();
	string username, password, phoneNumber, fullname;
	cout << "Type \"back\" or \"Back\" or \"BACK\" to return to Guest menu" << endl;
	cout << "Enter your username: ";
	getline(cin, username);
	if (username == "back" || username == "Back" || username == "BACK") return true;
	for (int i = 0; i < memberList.size(); i++) {
		if (memberList[i].getUsername() == username) {
			cout << "Username existed" << endl;
			return true;
		}
	}
	cout << "Enter your password: ";
	getline(cin, password);
	if (password == "back" || password == "Back" || password == "BACK") return true;
	cout << "Enter your Phone Number: ";
	getline(cin, phoneNumber);
	if (phoneNumber == "back" || phoneNumber == "Back" || phoneNumber == "BACK") return true;
	cout << "Enter your fullname: ";
	getline(cin, fullname);
	if (fullname == "back" || fullname == "Back" || fullname == "BACK") return true;
	member = Member(username, password, phoneNumber, fullname);
	member.addMember(member);
	cout << "Register successfully!" << endl;
	return false;
}

int Guest::mainMenu()
{
	cout << "-----Guest Menu-----" << endl;
	cout << "1. Search Books" << endl;
	cout << "2. Sample Collection" << endl;
	cout << "3. Register" << endl;
	cout << "4. Logout" << endl;
	return 4;
}

int Guest::sampleCollectionMenu()
{
	vector<Collection>& collectionList = this->getCollectionList();
	cout << "-----Sample Collection-----" << endl;
	return this->displayBooksInCollection(collectionList[0]);
}


