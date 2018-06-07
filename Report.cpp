#include "Report.h"

void Report::getInput()
{
	do
	{
		std::cout << "What would you like to do?" << std::endl;
		std::string input;
		getline(std::cin, input);
		chosenOption = std::stoi(input);
	} while (chosenOption < 0 || chosenOption > 7);
}
void Report::runOptions()
{
	switch (chosenOption)
	{
	case 1:
		showInventoryList();
		break;
	case 2:
		showWholesaleList();
		break;
	case 3:
		showRetailList();
		break;
	case 4:
		showQuantityList();
		break;
	case 5:
		showCostList();
		break;
	case 6:
		showAgeList();
		break;
	}
}
void Report::showInventoryList(Bundle books)
{

}
void Report::showWholesaleList()
{

}
void Report::showRetailList()
{

}
void Report::showQuantityList()
{

}
void Report::showCostList()
{

}
void Report::showAgeList()
{

}