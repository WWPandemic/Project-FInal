#define _CRT_SECURE_NO_WARNINGS
#include "MainMenu.h"
#include "Report.h"
#include "CashRegister.h"
#include "Inventory.h"

void MainMenu::getInput()
{
	do
	{
		std::cout << "What would you like to do?" << std::endl;
		std::string input;
		getline(std::cin, input);
		try {
			chosenOption = std::stoi(input);
		}
		catch (...)
		{
			chosenOption = -1;
		}
		if (chosenOption < 0 || chosenOption > 4)
		{
			std::cout << "Enter a valid number" << std::endl;
		}
	} while (chosenOption < 0 || chosenOption > 4);
	clearScreen();
}

void MainMenu::runOptions()
{
	switch (chosenOption)
	{
	case 1:
		useInventoryModule(&menuBooks);
		break;
	case 2:
		useCashierModule(menuBooks);
		break;
	case 3:
		useReportModule(menuBooks);
		break;
	default:
		isUsingMenu = false;
		break;
	}
}

void MainMenu::useReportModule(Bundle b)
{
	Report reportMenu = Report(b);
	reportMenu.runMenu();

}
void MainMenu::useCashierModule(Bundle &b)
{
	CashRegister cashRegister = CashRegister(b);
	cashRegister.runMenu();

}
void MainMenu::useInventoryModule(Bundle *b)
{
	Inventory inventory = Inventory(b);
	inventory.runMenu();
}

