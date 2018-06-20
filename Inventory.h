#pragma once
#include "Menu.h"
#include <iostream>
#include "Bundle.h"

class Inventory : public Menu
{
private:
	Bundle * books;

	
	void getInput();//Gets user input for menu options
	void runOptions(); //Uses user input to select which function to run

	void LookUpBooks(); //Print the details for a user specified book
	void AddNewBooks(); //Adds a book to bundle after all information is entered by user
	void DeleteBooks(); //Removes user specified book from bundle
	void EditBookInformation(); //Edit any field of a user specified book

	int searchByTitle(std::string title); //Returns the index of a book with the correct title
	int searchByISBN(int ISBN); //Returns the index of a book with the correct ISBN

	std::string enterString();
	int enterInteger();
	double enterDouble();

public:
	Inventory() //Defualt constructor
	{
		chosenOption = 5;//defaults to main menu

		introductions[0] = "---------------------------------------------------------------------------",
			introductions[1] = "                     Welcome to the Inventory Module:",
			introductions[2] = "This module allows you to look at the books inventory",
			introductions[3] = "And all change information related to the inventory",
			introductions[4] = "You can use this module to:",
			introductions[5] = "1 - Look Up Books",
			introductions[6] = "   Use a name or the ISBN of a book to find its information",
			introductions[7] = "2 - Add New Books",
			introductions[8] = "    Enter all information relating to a book and add it to the inventory",
			introductions[9] = "3 - Delete Books",
			introductions[10] = "    Find and remove any books from the inventory",
			introductions[11] = "4 - Change informations",
			introductions[12] = "    Find any book and edit its information",
			introductions[13] = "5 - Go back to main menu",
			introductions[14] = "---------------------------------------------------------------------------";
		usedIntroLines = 15;
	};

	Inventory(Bundle* b) //Constuctor that sets books
	{
		chosenOption = 5;//defaults to main menu
		books = b;

		introductions[0] = "---------------------------------------------------------------------------",
			introductions[1] = "                     Welcome to the Inventory Module:",
			introductions[2] = "This module allows you to look at the books inventory",
			introductions[3] = "And all change information related to the inventory",
			introductions[4] = "You can use this module to:",
			introductions[5] = "1 - Look Up Books",
			introductions[6] = "    Use a name or the ISBN of a book to find its information",
			introductions[7] = "2 - Add New Books",
			introductions[8] = "    Enter all information relating to a book and add it to the inventory",
			introductions[9] = "3 - Delete Books",
			introductions[10] = "    Find and remove any books from the inventory",
			introductions[11] = "4 - Change informations",
			introductions[12] = "    Find any book and edit its information",
			introductions[13] = "5 - Go back to main menu",
			introductions[14] = "---------------------------------------------------------------------------";
		usedIntroLines = 15;
	};

	~Inventory() 
	{} //Destructor
};
