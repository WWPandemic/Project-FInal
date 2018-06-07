#pragma once
#include "Bundle.h"
#include <string>
#include <iostream>

class Menu
{
private:
	void outputIntroduction()
	{
		for (int ind = 0; ind < introductions->length; ind++)
		{
			std::cout << introductions[ind] << std::endl;
		}
	}
	void getInput();
	void runOptions();
protected:
	bool isUsingMenu;
	int chosenOption;
	std::string* introductions;
	Bundle menuBooks;
public:
	Menu();
	~Menu();
	void runMenu()
	{
		do
		{
			outputIntroduction();
			getInput();
			runOptions();
		} while (isUsingMenu);
	}
};
