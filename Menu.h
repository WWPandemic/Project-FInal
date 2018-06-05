#pragma once
#include <string>

class Menu
{
private:
	void outputIntroduction()
	{
		for (int ind = 0; ind < introductions->length; ind++)
		{
			cout << introductions[ind] << endl;
		}
	}
	void getInput();
	void runOptions();
protected:
	bool isUsingMenu;
	int chosenOption;
	std::string* introductions;
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
