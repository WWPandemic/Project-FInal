#define _CRT_SECURE_NO_WARNINGS
#include "Report.h"
#include <iomanip>

/*
Function: getInput
Author: Evren Keskin
Parameters: none
Returns: none
Description:
	This function runs a loop asking the user for a number 
	as the answer to what option they want to run
	and checks that they enter a valid number in the process
*/
void Report::getInput()
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
		if (chosenOption < 0 || chosenOption > 7)
		{
			std::cout << "Enter a valid number" << std::endl;
		}
	} while (chosenOption < 0 || chosenOption > 7);
	clearScreen();
}
/*
Function: runOptions
Author: Evren Keskin
Parameters: none
Returns:none
Description:
	This function has a switch that chooses the option
	the user was asked to choose, and runs that option
	and if they're going to look a list, pauses the menu
	on that printed list
*/
void Report::runOptions()
{
	switch (chosenOption)
	{
	case 1:
		showInventoryList(menuBooks);
		break;
	case 2:
		showWholesaleList(menuBooks);
		break;
	case 3:
		showRetailList(menuBooks);
		break;
	case 4:
		showQuantityList(menuBooks);
		break;
	case 5:
		showCostList(menuBooks);
		break;
	case 6:
		showAgeList(menuBooks);
		break;
	case 7:
	default:
		isUsingMenu = false;
		break;
	}
	if(isUsingMenu)
		pauseMenu();
}
/*
Function: showInventoryList
Author: Evren Keskin
Parameters:
Bundle books // the Bundle to show the books from
Returns:none
Description:
	This function takes the Bundle in the report module and 
	prints the list in the default alphabetical order
	with all attributes of every book
*/
void Report::showInventoryList(Bundle books)
{
	Array<Book> b = books.getArray();
	for (int ind = 0; ind < books.getSize(); ind++)
	{
		std::cout << ind + 1 << ") " << b[ind].toString() << std::endl << std::endl;
	}
}
/*
Function: showWholesaleList
Author:	Evren Keskin
Parameters:	
Bundle books // the Bundle to show the books from
Returns:none
Description:
	This function takes the Bundle in the report module and
	prints the total wholesale cost that was needed to 
	buy the total quantity of every book
*/
void Report::showWholesaleList(Bundle books)
{
	Array<Book> b = books.getArray();
	double total = 0;
	for (int ind = 0; ind < books.getSize(); ind++)
	{
		double d = b[ind].getCost() * b[ind].getQuantity();
		std::cout << std::setw(2) << std::right << ind + 1 << ") Wholesale cost of: $" 
			<< std::setw(5) << std::left << d << " for all copies of " << b[ind].getTitle() +
			" by " + b[ind].getAuthor() <<  std::endl << std::endl;
		total += d;
	}
	std::cout << "This adds to a total cost of " << total << "$" << std::endl;
}
/*
Function: showRetailList
Author:	Evren Keskin
Parameters:
Bundle books // the Bundle to show the books from
Returns:none
Description:
	This function takes the Bundle in the report module and
	prints the total retail price that is possible
	when the total quantity of every book is sold
*/
void Report::showRetailList(Bundle books)
{
	Array<Book> b = books.getArray();
	double total = 0;
	for (int ind = 0; ind < books.getSize(); ind++)
	{
		double d = b[ind].getPrice() * b[ind].getQuantity();
		std::cout << std::setw(2) << std::right << ind + 1 << ") Retail Price of : $" 
			<< std::setw(5) << std::left << d << " for all copies of " << b[ind].getTitle() +
			" by " + b[ind].getAuthor() << std::endl << std::endl; 
		total += d;
	}
	std::cout << "This adds to a total retail profit of " << total << "$" << std::endl;
}
/*
Function: showQuantityList
Author:	Evren Keskin
Parameters:
Bundle books // the Bundle to show the books from
Returns:none
Description:
	This function takes the Bundle in the report module and
	organizes the books by their quantity, max to min,
	and prints out the quantity list
*/
void Report::showQuantityList(Bundle books)
{
	Array<Book> b = books.getArray();
	double total = 0;

	for (int ind = 0; ind < books.getSize(); ind++)
	{
		int maxQuantity = b[ind].getQuantity();
		int swapInd = ind;
		for (int target = ind; target < books.getSize(); target++)
		{
			if (b[target].getQuantity() > maxQuantity)
			{
				swapInd = target;
				maxQuantity = b[target].getQuantity();
			}
		}
		if (swapInd != ind)
		{
			Book temp = b[ind];
			b[ind] = b[swapInd];
			b[swapInd] = temp;
		}
	}

	for (int ind = 0; ind < books.getSize(); ind++)
	{
		double d = b[ind].getQuantity();
		std::cout << "There are " << d << " copies of " << 
			b[ind].getTitle() + " by " + b[ind].getAuthor() << std::endl << std::endl;
		total += d;
	}
	std::cout << "This makes a total of " << total << " books" << std::endl;
}
/*
Function: showCostList
Author:	Evren Keskin
Parameters:
Bundle books // the Bundle to show the books from
Returns:none
Description:
	This function takes the Bundle in the report module and
	organizes the books by their wholesale cost per book
	and prints out the wholesale cost list
*/
void Report::showCostList(Bundle books)
{
	Array<Book> b = books.getArray();
	double total = 0;

	for (int ind = 0; ind < books.getSize(); ind++)
	{
		double maxCost = b[ind].getCost();
		int swapInd = ind;
		for (int target = ind; target < books.getSize(); target++)
		{
			if (b[target].getCost() > maxCost)
			{
				swapInd = target;
				maxCost = b[target].getCost();
			}
		}
		if (swapInd != ind)
		{
			Book temp = b[ind];
			b[ind] = b[swapInd];
			b[swapInd] = temp;
		}
	}

	for (int ind = 0; ind < books.getSize(); ind++)
	{
		double d = b[ind].getCost();
		std::cout << "Wholesale cost of " << d << " for the book " << 
			b[ind].getTitle() + " by " + b[ind].getAuthor() <<  std::endl << std::endl;
		total += d;
	}
}
/*
Function: showAgeList
Author:	Evren Keskin
Parameters:
Bundle books // the Bundle to show the books from
Returns:none
Description:
	This function takes the Bundle from the report module and
	organizes the books by their date of entry into the inventory, old to new
	abd prints out the age list
*/
void Report::showAgeList(Bundle books)
{
	Array<Book> b = books.getArray();

	for (int ind = 0; ind < books.getSize(); ind++)
	{
		Date newestDate = b[ind].getDate();
		int swapInd = ind;
		for (int target = ind; target < books.getSize(); target++)
		{
			if ( b[target].getDate() <= newestDate)
			{
				swapInd = target;
				newestDate = b[target].getDate();
			}
		}
		if (swapInd != ind)
		{
			Book temp = b[ind];
			b[ind] = b[swapInd];
			b[swapInd] = temp;
		}
	}

	for (int ind = 0; ind < books.getSize(); ind++)
	{
		Date d = b[ind].getDate();
		std::cout << "On the date " << d << " the book " <<
			b[ind].getTitle() + " by " + b[ind].getAuthor() <<
			" was added to the inventory" << std::endl << std::endl;
	}
}

/*
Function: pauseMenu
Author:	Evren Keskin
Parameters:none
Returns: none
Description:
	This function is used for UI prettification
	and simply asks the user to press enter before cleaning the console
	and returning to its caller
*/
void Report::pauseMenu()
{
	std::cout << "Press <Enter> to return to the Report Module" << std::endl;
	std::string temp;
	std::getline(std::cin,temp);
	clearScreen();
}

/*
Constructor: Report
Author:	Evren Keskin
Parameters:
Bundle b // the Bundle to show the books from
Returns:
Report object
Description:
	This constructor makes a new Report module
	with its menuBooks attribute set to the parameter Bundle,
	the default chosenOption being the return to menu option,
	and the module introductions set according to
	the Report Modules requirements
*/
Report::Report(Bundle b)
{
	menuBooks = b;
	chosenOption = 7;//defaults to main menu

	introductions[0] =  "---------------------------------------------------------------------------";
	introductions[1] =  "                      Welcome to the report module:";
	introductions[2] =  "           This module gives any requested report of the inventory";
	introductions[3] =  "                 And all information related to the inventory";
	introductions[4] =  "                        These reports include:";
	introductions[5] =  "1 - An Inventory List";
	introductions[6] =  "    A list of all information on all books in inventory";
	introductions[7] =  "2 - An Inventory  Wholesale  Value List";
	introductions[8] =  "    A list of the wholesale value of all books in inventory";
	introductions[9] =  "    and the total wholesale value of all books";
	introductions[10] = "3 - An Inventory  Retail  Value List";
	introductions[11] = "    A list of the retail value of all books in inventory";
	introductions[12] = "    and the total retail value of the inventory";
	introductions[13] = "4 - A List of Quantity";
	introductions[14] = "    A list of all books in the inventory sorted by quantity";
	introductions[15] = "    The books with the greatest quantity on hand will be listed first";
	introductions[16] = "5 - A List by Cost";
	introductions[17] = "    A list of all books in the inventory sorted by cost";
	introductions[18] = "    The books with the greatest wholesale cost will be listed first";
	introductions[19] = "6 - A List by Age";
	introductions[20] = "    A list of all books in the inventory sorted by purchase date";
	introductions[21] = "	The  books that have been in the inventory longest will be listed first";
	introductions[22] = "7 - Go back to the main menu";
	introductions[23] = "---------------------------------------------------------------------------";
	usedIntroLines = 24;
}
