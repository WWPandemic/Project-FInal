#pragma once
#include "Menu.h"
#include <iostream>

class MainMenu : public Menu
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
		} while (chosenOption < 0 || chosenOption > 4);
	}
	void runOptions()
	{
		//needs bundle.cpp to be built before developement
		isUsingMenu = false;
	}
public:
	MainMenu()
	{
		chosenOption = 4;//defaults to exit
		introductions = new std::string[]
		{
			"---------------------------------------------------------------------------",
			"                    Welcome to the Serepdipity Bookstore:",
			"This is a point-of-sale program to help the Serepdipity employees",
			"And all information related to the inventory",
			"You have the option to:",
			"1 - Open the Inventory Module",
			"    Allows editing of all information on all books in inventory",
			"2 - Open the Cashier Module",
			"    Allows a transaction to be recorded into the database",
			"3 - Open the Report Database",
			"    Allows a quick report on any/all information in the inventory",
			"4 - Exit Program",
			"---------------------------------------------------------------------------"
		};
	}
};