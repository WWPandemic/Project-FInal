#pragma once
#include "Menu.h"
#include <iostream>
#include "Bundle.h"

class Inventory : public Menu
{
private:
	//outputIntroduction unmodified
	void getInput()
	{
		do
		{
			std::cout << "What would you like to do?" << std::endl;
			std::string input;
			getline(std::cin, input);
			chosenOption = std::stoi(input);
		} while (chosenOption < 0 || chosenOption > 5);
	}
	void runOptions()
	{
		switch (chosenOption)
		{
		case 5: break;
		default: break;
		}
	};
	//Bundle books;
	void LookUpBooks() {}
	void AddNewBooks() {}
	void DeleteBooks() {}
	void EditBookInformation() {}
public:
	Inventory()
	{
		chosenOption = 5;//defaults to main menu
		 
		introductions[0] =	"---------------------------------------------------------------------------",
		introductions[1] =	"                     Welcome to the Inventory Module:",
		introductions[2] =	"This module allows you to look at the books inventory",
		introductions[3] =	"And all change information related to the inventory",
		introductions[4] =	"You can use this module to:",
		introductions[5] =	"1 - Look Up Books",
		introductions[6] =	"   Use a name or the ISBN of a book to find its information",
		introductions[7] =	"2 - Add New Books",
		introductions[8] =	"    Enter all information relating to a book and add it to the inventory",
		introductions[9] =	"3 - Delete Books",
		introductions[10] =	"    Find and remove any books from the inventory",
		introductions[11] =	"4 - Change informations",
		introductions[12] =	"    Find any book and edit its information",
		introductions[13] =	"5 - Go back to main menu",
		introductions[14] =	"---------------------------------------------------------------------------"
		usedIntroLines = 15;
	};
};
