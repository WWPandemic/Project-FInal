#pragma once
#include <string>

class Menu
{
private:

	void outputIntroduction();
	
	void getInput();
	void runOptions();
protected:
	bool isUsingMenu;
	string* introductions;
public:
	Menu();
	~Menu();
	void runMenu();
};
