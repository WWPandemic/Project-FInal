#pragma once
#include "Menu.h"
#include <iostream>

class Report : public Menu
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
		} while (chosenOption < 0 || chosenOption > 7);
	}
	void runOptions()
	{
		//needs bundle.cpp to be built before developement
		isUsingMenu = false;
	}
public:
	Report()
	{
		chosenOption = 7;//defaults to main menu
		introductions = new std::string[]
		{
			"---------------------------------------------------------------------------",
			"                    Welcome to the report module:",
			"This module gives any requested report of the inventory",
			"And all information related to the inventory",
			"These reports include:",
			"1 - An Inventory List",
			"    A list of all information on all books in inventory",
			"2 - An Inventory  Wholesale  Value List",
			"    A list of the wholesale value of all books in inventory",
			"    and the total wholesale value of all books",
			"3 - An Inventory  Retail  Value List",
			"    A list of the retail value of all books in inventory",
			"    and the total retail value of the inventory",
			"4 - A List of Quantity",
			"    A list of all books in the inventory sorted by quantity",
			"    The books with the greatest quantity on hand will be listed first",
			"5 - A List by Cost",
			"    A list of all books in the inventory sorted by cost",
			"    The books with the greatest wholesale cost will be listed first",
			"6 - A List by Age",
			"    A list of all books in the inventory sorted by purchase date",
			"	The  books that have been in the inventory longest will be listed first",
			"7 - Go back to the main menu",
			"---------------------------------------------------------------------------"
		};
	}
};