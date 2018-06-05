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
public:
	Inventory()
	{
		chosenOption = 5;//defaults to main menu
		introductions = new std::string[]
		{
			"---------------------------------------------------------------------------",
			"                     Welcome to the Inventory Module:",
			"This module allows you to look at the books inventory",
			"And all change information related to the inventory",
			"You can use this module to:",
			"1 - Look Up Books",
			"   Use a name or the ISBN of a book to find its information",
			"2 - Add New Books",
			"    Enter all information relating to a book and add it to the inventory",
			"3 - Delete Books",
			"    Find and remove any books from the inventory",
			"4 - Change informations",
			"    Find any book and edit its information",
			"5 - Go back to main menu",
			"---------------------------------------------------------------------------"
		};
	};
};