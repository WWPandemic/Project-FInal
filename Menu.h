#pragma once
#include "Bundle.h"
#include <string>
#include <iostream>

class Menu
{
private:
	virtual void outputIntroduction();
	virtual void getInput();
	virtual void runOptions();
protected:
	void clearScreen();
	bool isUsingMenu;
	int chosenOption;
	std::string introductions[100];
	int usedIntroLines;
	Bundle menuBooks;
public:
	Menu();
	void runMenu();
};
