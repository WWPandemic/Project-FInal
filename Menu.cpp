#include "Menu.h"
#include <iostream>

using namespace std;


void Menu::getInput() {}
void Menu::runOptions()
{
	isUsingMenu = false;
}
Menu::Menu()
{
	isUsingMenu = true;
	introductions = new string[]
	{
		"This is the parent menu class",
		"If you are seeing this, something is wrong"
	};
}
Menu::~Menu()
{
	delete introductions;
}