#pragma once
#include "Menu.h"

class MainMenu : public Menu
{
private:
	//outputIntroduction unmodified
	void getInput();
	void runOptions();
	void useReportModule(Bundle b);
	void useCashierModule(Bundle b);
	void useInventoryModule(Bundle *b);
public:
	MainMenu(Bundle b)
	{
		chosenOption = 4;//defaults to exit
		menuBooks = b;
		introductions[0] = "---------------------------------------------------------------------------";
		introductions[1] = "                    Welcome to the Serepdipity Bookstore:";
		introductions[2] = "This is a point-of-sale program to help the Serepdipity employees";
		introductions[3] = "And all information related to the inventory";
		introductions[4] = "You have the option to:";
		introductions[5] = "1 - Open the Inventory Module";
		introductions[6] = "    Allows editing of all information on all books in inventory";
		introductions[7] = "2 - Open the Cashier Module";
		introductions[8] = "    Allows a transaction to be recorded into the database";
		introductions[9] = "3 - Open the Report Database";
		introductions[10] = "    Allows a quick report on any/all information in the inventory";
		introductions[11] = "4 - Exit Program";
		introductions[12] = "---------------------------------------------------------------------------";
		usedIntroLines = 13;
	}
};
