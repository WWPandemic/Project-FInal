#include <string>
#include <iostream>

using namespace std;

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
	void getInput(){}
	void runOptions()
	{	
		isUsingMenu = false;
	}
protected:
	bool isUsingMenu;
	string* introductions;
public:
	Menu()
	{
		isUsingMenu = true;
		introductions = new string[]
		{
			"This is the parent menu class",
			"If you are seeing this, something is wrong"
		};
	}
	~Menu()
	{
		delete introductions;
	}

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