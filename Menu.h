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
	std::string* introductions;
public:
	Menu();
	~Menu();
	void runMenu();
};
