#pragma once
#include "Menu.h"

class Report : public Menu
{
private:
	//outputIntroduction unmodified
	void getInput();
	void runOptions();

	//options of the report menu
	void showInventoryList(Bundle b);
	void showWholesaleList(Bundle b);
	void showRetailList(Bundle b);
	void showQuantityList(Bundle b);
	void showCostList(Bundle b);
	void showAgeList(Bundle b);
	void pauseMenu();
public:
	//Report();
	Report(Bundle b);
};

