#include "Menu.h"
#include <iostream>

using namespace std;

void Menu::outputIntroduction()
{
	for (int ind = 0; ind < usedIntroLines; ind++)
	{
		cout << introductions[ind] << endl;
	}
}
void Menu::getInput()
{
	cout << "You're using the default menu" << endl;
} 
void Menu::runOptions()
{
	isUsingMenu = false;
}
void Menu::clearScreen()
{
	system("CLS");
}
void Menu::runMenu()
{
	do
	{
		outputIntroduction();
		getInput();
		runOptions();
	} while (isUsingMenu);
}
Menu::Menu()
{
	isUsingMenu = true;
	introductions[0] = "This is the parent menu class";
	introductions[1] = "If you are seeing this, something is wrong";
	usedIntroLines = 2;
}
