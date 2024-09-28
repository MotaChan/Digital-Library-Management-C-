#include <iostream>
#include <string>
#include <cstdlib>
#include "Admin.h"
#include "Guest.h"
#include "Member.h"

using namespace std;

const int LIBRARY_OPTIONS = 3, SUBSCRIBED_COLLECTION_BOOK_MENU_OPTIONS = 3;

int main() {
	Admin baseAdmin =  Admin("Long3020", "longgnol3020", "0328717107", "Truong Hoang Long");
	baseAdmin.addAdmin(baseAdmin);
	baseAdmin.createCollection();
	Guest temp, guest;
	Admin* admin = nullptr;
	Member* member = nullptr;
	Book* book = nullptr;
	bool flag;
	int userOption;
	char userInput;
	while (true) {
		cout << "-----Library Menu-----\n1. Login as Guest\n2. Login\n3. Exit\n";
		userOption = temp.chooseOption(LIBRARY_OPTIONS);
		switch (userOption) {
		case 1:
			guest = Guest();
			flag = true;
			while (flag) {
				userOption = guest.chooseOption(guest.mainMenu());
				switch (userOption) {
				case 1:
					flag = true;
					while (flag) {
						userOption = guest.chooseOption(guest.searchBooksMenu());
						switch (userOption) {
						case 1:
							book = guest.searchBookByTitle();
							if (book == nullptr) break;
							book->display();
							cout << "Press ENTER to read it or else return to Search Books Menu" << endl;
							cin.get(userInput);
							if (userInput != '\n') break;
							guest.readBook(*book);
							break;
						case 2:
							book = guest.searchBookBySerial(); 
							if (book == nullptr) break;
							book->display();
							cout << "Press ENTER to read it or else return to Search Books Menu" << endl;
							cin.get(userInput);
							if (userInput != '\n') break;
							guest.readBook(*book);
							break;
						case 3:
							flag = false;
							break;
						}
					}
					flag = true;
					break;
				case 2:
					flag = true;
					while (flag) {
						int options = guest.displayBooksInCollection(*guest.getCollection(0));
						cout << ++options << ". Exit" << endl;
						userOption = guest.chooseOption(options);
						if (userOption == options) break;
						book = guest.getBook(*guest.getCollection(0), userOption);
						book->display();
						cout << "Press ENTER to read it or else return to Sample Collection Menu" << endl;
						cin.get(userInput);
						if (userInput != '\n') {}
						else guest.readBook(*book);
					}
					break;
				case 3:
					flag = guest.registerMember();
					break;
				case 4:
					flag = false;
					break;
				}
			}
			break;
		case 2:
			flag = true;
			while (flag) {
				userOption = temp.chooseOption(admin->loginMenu());
				switch (userOption) {
				case 1:
					admin = admin->login(); 
					if (admin == nullptr) break;
					cout << "Login successfully!" << endl;
					flag = true;
					while (flag) {
						userOption = admin->chooseOption(admin->mainMenu());
						switch (userOption) {
						case 1:
							admin->createAdmin();
							break;
						case 2:
							flag = true;
							while (flag) {
								userOption = admin->chooseOption(admin->searchBooksMenu());
								switch (userOption) {
								case 1:
									book = admin->searchBookByTitle();
									if (book == nullptr) break;
									admin->manageBook(book);
									break;
								case 2:
									book = admin->searchBookBySerial();
									if (book == nullptr) break;
									admin->manageBook(book);
									break;
								case 3:
									flag = false;
									break;
								}
							}
							flag = true;
							break;
						case 3:
							flag = true;
							while (flag) {
								int options = admin->displayHiddenBookList();
								userOption = admin->chooseOption(options);
								if (userOption == options) break;
								admin->showBook(userOption);
							}
							break;
						case 4:
							admin->addBook();
							break;
						case 5:
							admin->createCollection();
							break;
						case 6:
							flag = true;
							while (flag) {
								int collectionListOptions = admin->displayCollectionList();
								int chosenCollection = admin->chooseOption(collectionListOptions);
								if (chosenCollection == collectionListOptions) break;
								flag = true;
								while (flag) {
									userOption = admin->chooseOption(admin->manageCollectionMenu(chosenCollection));
									switch (userOption) {
									case 1:
										admin->removeCollection(chosenCollection);
										break;
									case 2:
										admin->editCollection(chosenCollection);
										break;
									case 3:
										flag = true;
										while (flag) {
											int booksInCollectionOptions = admin->displayBooksInCollection(chosenCollection);
											int chosenBook = admin->chooseOption(booksInCollectionOptions);
											if (chosenBook == booksInCollectionOptions) break;
											else if (chosenBook == booksInCollectionOptions - 1) {
												flag = true;
												while (flag) {
													userOption = admin->chooseOption(admin->addBookInCollectionMenu());
													switch (userOption) {
													case 1:
														book = admin->searchBookByTitle();
														if (book == nullptr) break;
														admin->addBookInCollection(chosenCollection, *book);
														break;
													case 2:
														book = admin->searchBookBySerial();
														if (book == nullptr) break;
														admin->addBookInCollection(chosenCollection, *book);
														break;
													case 3:
														flag = false;
														break;
													}
												}
												flag = true;
												break;
											}
											flag = true;
											while (flag) {
												userOption = admin->chooseOption(admin->manageBookInCollectionMenu(chosenCollection, chosenBook));
												switch (userOption) {
												case 1:
													admin->removeBookInCollection(chosenCollection, chosenBook);
													flag = false;
													break;
												case 2:
													admin->readBookInCollection(chosenCollection, chosenBook);
													break;
												case 3:
													flag = false;
													break;
												}
											}
											flag = true;
										}
										break;
									case 4:
										flag = false;
										break;
									}
								}
								flag = true;
							}
							break;
						case 7:
							flag = true;
							while (flag) {
								userOption = admin->chooseOption(admin->userProfileMenu());
								switch (userOption) {
								case 1:
									admin->display();
									break;
								case 2:
									flag = true;
									while (flag) {
										userOption = admin->chooseOption(admin->userEditProfileMenu());
										switch (userOption) {
										case 1:
											admin->changeUsername();
											break;
										case 2:
											admin->changePassword();
											break;
										case 3:
											admin->changePhoneNumber();
											break;
										case 4:
											admin->changeFullname();
											break;
										case 5:
											flag = false;
											break;
										}
									}
									flag = true;
									break;
								case 3:
									flag = false;
									break;
								}
							}
							flag = true;
							break;
						case 8:
							flag = false;
							break;
						}
					}
					flag = true;
					break;
				case 2:
					member= member->login(); 
					if (member == nullptr) break;
					flag = true;
					while (flag) {
						userOption = member->chooseOption(member->mainMenu());
						switch (userOption) {
						case 1:
							flag = true;
							while (flag) {
								userOption = member->chooseOption(member->searchBooksMenu());
								switch (userOption) {
								case 1:
									book = member->searchBookByTitle();
									if (book == nullptr) break;
									member->readAndBorrowBook(*book);
									break;
								case 2:
									book = member->searchBookBySerial();
									if (book == nullptr) break;
									member->readAndBorrowBook(*book);
									break;
								case 3:
									flag = false;
									break;
								}
							}
							flag = true;
							break;
						case 2:
							flag = true;
							while (flag) {
								int borrowListOptions = member->displayBorrowList();
								int chosenBorrowedBook = member->chooseOption(borrowListOptions);
								if (chosenBorrowedBook == borrowListOptions) break;
								flag = true;
								while (flag) {
									userOption = member->chooseOption(member->borrowedBookMenu(chosenBorrowedBook));
									switch (userOption) {
									case 1:
										member->readBookInBorrowList(chosenBorrowedBook);
										break;
									case 2:
										member->returnBook(chosenBorrowedBook - 1);
										flag = false;
										break;
									case 3:
										flag = false;
										break;
									}
								}
								flag = true;
							}
							flag = true;
							break;
						case 3:
							flag = true;
							while (flag) {
								userOption = member->chooseOption(member->collectionMenu());
								switch (userOption) {
								case 1:
									flag = true;
									while (flag) {
										int collectionOptions = member->displayCollectionList();
										int chosenCollection = member->chooseOption(collectionOptions);
										if (chosenCollection == collectionOptions) break;
										flag = true;
										while (flag) {
											int bookOptions = member->chosenFromAllCollectionsMenu(chosenCollection);
											if (bookOptions == -1) break;
											int chosenBook = member->chooseOption(bookOptions);
											if (chosenBook == bookOptions) break;
											flag = true;
											while (flag) {
												bool borrowOrNot;
												try { borrowOrNot = member->subscribedCollectionBookChosenFromAllCollectionsMenu(chosenCollection, chosenBook); }
												catch (Member::BookBorrowed) { flag = false; break; }
												userOption = member->chooseOption(SUBSCRIBED_COLLECTION_BOOK_MENU_OPTIONS);
												switch (userOption) {
												case 1:
													member->readBookInSubscribedCollectionChosenFromAllCollections(chosenCollection, chosenBook);
													break;
												case 2:
													if (borrowOrNot) member->borrowBookChosenFromAllCollections(chosenCollection, chosenBook);
													else member->returnBookChosenFromAllCollections(chosenCollection, chosenBook);
													break;
												case 3:
													flag = false;
													break;
												}
											}
											flag = true;
										}
									}
									break;
								case 2:
									flag = true;
									while (flag) {
										int subscribedCollectionOptions = member->displaySubscribedCollectionList();
										int chosenCollection = member->chooseOption(subscribedCollectionOptions);
										if (chosenCollection == subscribedCollectionOptions) break;
										flag = true;
										while (flag) {
											userOption = member->chooseOption(member->unsubOrShowBooksMenu(chosenCollection));
											switch (userOption) {
											case 1:
												member->unsubscribeCollection(chosenCollection - 1);
												flag = false;
												break;
											case 2:
												flag = true;
												while (flag) {
													int bookOptions = member->displayBooksInSubscribedCollection(chosenCollection);
													int chosenBook = member->chooseOption(bookOptions);
													if (chosenBook == bookOptions) break;
													flag = true;
													while (flag) {
														bool borrowOrNot;
														try { borrowOrNot = member->subscribedCollectionBookChosenFromSubscribedCollectionsMenu(chosenCollection, chosenBook); }
														catch (Member::BookBorrowed) { flag = false; break; }
														userOption = member->chooseOption(SUBSCRIBED_COLLECTION_BOOK_MENU_OPTIONS);
														switch (userOption) {
														case 1:
															member->readBookInSubscribedCollectionChosenFromSubscribedCollections(chosenCollection, chosenBook);
															break;
														case 2:
															if (borrowOrNot) member->borrowBookChosenFromSubscribedCollections(chosenCollection, chosenBook);
															else member->returnBookChosenFromSubscribedCollections(chosenCollection, chosenBook);
															break;
														case 3:
															flag = false;
															break;
														}
													}
													flag = true;
												}
												break;
											case 3:
												flag = false;
												break;
											}
										}
										flag = true;
									}
									break;
								case 3:
									flag = false;
									break;
								}
							}
							flag = true;
							break;
						case 4:
							flag = true;
							while (flag) {
								userOption = member->chooseOption(member->userProfileMenu());
								switch (userOption) {
								case 1:
									member->display();
									break;
								case 2:
									flag = true;
									while (flag) {
										userOption = member->chooseOption(member->userEditProfileMenu());
										switch (userOption) {
										case 1:
											member->changeUsername();
											break;
										case 2:
											member->changePassword();
											break;
										case 3:
											member->changePhoneNumber();
											break;
										case 4:
											member->changeFullname();
											break;
										case 5:
											flag = false;
											break;
										}
									}
									flag = true;
									break;
								case 3:
									flag = false;
									break;
								}
							}
							flag = true;
							break;
						case 5:
							flag = false;
							break;
						}
					}
					flag = true;
					break;
				case 3:
					flag = false;
					break;
				}
			}
			break;
		case 3:
			exit(0);
		}
	}
	return 0;
}