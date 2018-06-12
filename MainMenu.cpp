#define _CRT_SECURE_NO_WARNINGS
#include "MainMenu.h"
#include "Report.h"
#include "CashRegister.h"
#include "Inventory.h"

void MainMenu::runOptions()
{
	switch (chosenOption)
	{
	case 1:
		useReportModule(menuBooks);
		break;
	case 2:
		useCashierModule(menuBooks);
		break;
	case 3:
		useInventoryModule(menuBooks);
		break;
	default:
		isUsingMenu = false;
		break;
	}
}

void MainMenu::useReportModule(Bundle b)
{
	Report reportMenu = Report(menuBooks);
	reportMenu.runMenu();

}
void MainMenu::useCashierModule(Bundle b)
{
	CashRegister cashRegister = CashRegister(menuBooks);
	cashRegister.runMenu();

}
void MainMenu::useInventoryModule(Bundle b)
{
	Inventory inventory = Inventory(menuBooks);
	inventory.runMenu();
}
