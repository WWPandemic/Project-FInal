
#include <string>
#include <iostream>

using namespace std;

int main()
{
	Menu basic = Menu();
	basic.runMenu();

	return 0;
}

class Menu
{
private:
	bool isUsingMenu;
	string introductions[100];
	void outputIntroduction()
	{

	}
	void getInput()
	{

	}
	void runOptions()
	{
		isUsingMenu = false;
	}
public:
	Menu()
	{
		isUsingMenu = true;
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