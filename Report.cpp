#include "Report.h"

void Report::getInput()
{
	/* Gets input with range of numbers
	based on the amount of options
	*/
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
}
void Report::showInventoryList(Bundle books)
{
	for (int ind = 0; ind < books.getSize(); ind++)
	{
		books.printAll();
	}
}
void Report::showWholesaleList(Bundle books)
{
	Book *b = books.getBundle();
	double total = 0;
	for (int ind = 0; ind < books.getSize(); ind++)
	{
		double d = (*b).getWholesaleCost();
		std::cout << (*b).getTitle() + " " + (*b).getAuthor() + " " + (*b).getPublisher()
			<< " has wholesale cost of:" << d << std::endl;
		total += d;
	}
	std::cout << "This adds to a total cost of " << total << "$" << std::endl;
}
void Report::showRetailList(Bundle books)
{
	Book *b = books.getBundle();
	double total = 0;
	for (int ind = 0; ind < books.getSize(); ind++)
	{
		double d = (*b).getRetailPrice();
		std::cout << (*b).getTitle() + " " + (*b).getAuthor() + " " + (*b).getPublisher()
			<< " has the retail price of:" << d << std::endl;
		total += d;
	}
	std::cout << "This adds to a total cost of " << total << "$" << std::endl;
}
void Report::showQuantityList(Bundle books)
{
	/*This method sorts a copy of the books by their quantity on hand
	and prints a list of the books to the user
	*/
	Book *b = books.getBundle();
	double total = 0;

	for (int ind = 0; ind < books.getSize(); ind++)
	{
		int minQuantity = (*b).getQuantityOnHand();
		int swapInd = ind;
		for (int target = ind; target < books.getSize(); target++)
		{
			if ((*b).getQuantityOnHand() < minQuantity)
			{
				swapInd = target;
				minQuantity = (*b).getQuantityOnHand();
			}
		}
		if (swapInd != ind)
		{
			Book temp = *(b + ind);
			*(b + ind) = *(b + swapInd);
			*(b + swapInd) = temp;
		}
	}

	for (int ind = 0; ind < books.getSize(); ind++)
	{
		double d = (*b).getQuantityOnHand();
		std::cout << "There are " << d << " copies of " << 
			(*b).getTitle() + " " + (*b).getAuthor() + " " + (*b).getPublisher() << std::endl;
		total += d;
	}
	std::cout << "This makes a total of " << total << " books" << std::endl;

	//sort back to alphabetical order
	sortAlphabetically(books);
}
/*
A list of all books in the inventory, sorted by wholesale cost. 
The books with the greatest wholesale cost will be listed first.
*/
void Report::showCostList(Bundle books)
{
	Book *b = books.getBundle();
	double total = 0;

	for (int ind = 0; ind < books.getSize(); ind++)
	{
		int minCost = (*b).getWholesaleCost();
		int swapInd = ind;
		for (int target = ind; target < books.getSize(); target++)
		{
			if ((*b).getWholesaleCost() < minCost)
			{
				swapInd = target;
				minCost = (*b).getWholesaleCost();
			}
		}
		if (swapInd != ind)
		{
			Book temp = *(b + ind);
			*(b + ind) = *(b + swapInd);
			*(b + swapInd) = temp;
		}
	}

	for (int ind = 0; ind < books.getSize(); ind++)
	{
		double d = (*b).getWholesaleCost();
		std::cout << "Wholesale cost of " << d << " for the book " << 
			(*b).getTitle() + " " + (*b).getAuthor() + " " + (*b).getPublisher() <<  std::endl;
		total += d;
	}
	std::cout << "This adds to a total cost of " << total << "$" << std::endl;
	sortAlphabetically(books);
}
void Report::showAgeList(Bundle books)
{
	Book *b = books.getBundle();

	for (int ind = 0; ind < books.getSize(); ind++)
	{
		Date newestDate = (*b).getDateAdded();
		int swapInd = ind;
		for (int target = ind; target < books.getSize(); target++)
		{
			//DATE COMPARISON
			if (((*b).getDateAdded().getDate() + 2) <= (newestDate.getDate() + 2)
				&& ((*b).getDateAdded().getDate() + 0) <= (newestDate.getDate() + 0)
				&& ((*b).getDateAdded().getDate() + 1) <= (newestDate.getDate() + 1)
				)
			{
				swapInd = target;
				newestDate = (*b).getDateAdded();
			}
		}
		if (swapInd != ind)
		{
			Book temp = *(b + ind);
			*(b + ind) = *(b + swapInd);
			*(b + swapInd) = temp;
		}
	}

	for (int ind = 0; ind < books.getSize(); ind++)
	{
		Date d = (*b).getDateAdded();
		std::cout << "On the date " << d << " the book " <<
			(*b).getTitle() + " " + (*b).getAuthor() + " " + (*b).getPublisher() << 
			" was added to the inventory" << std::endl;
	}
	sortAlphabetically(books);
}

void Report::sortAlphabetically(Bundle books)
{
	//sort back to alphabetical order
	Book *b = books.getBundle();
	for (int ind = 0; ind < books.getSize(); ind++)
	{
		std::string smallestName = (*b).getTitle();
		int swapInd = ind;
		for (int target = ind; target < books.getSize(); target++)
		{
			if ((*b).getTitle() < smallestName)
			{
				swapInd = target;
				smallestName = (*b).getTitle();
			}
		}
		if (swapInd != ind)
		{
			Book temp = *(b + ind);
			*(b + ind) = *(b + swapInd);
			*(b + swapInd) = temp;
		}
	}
}

Report::Report(Bundle b)
{
	menuBooks = b;
	chosenOption = 7;//defaults to main menu

	introductions[0] = "---------------------------------------------------------------------------";
	introductions[1] = "                      Welcome to the report module:";
	introductions[2] = "           This module gives any requested report of the inventory";
	introductions[3] = "                 And all information related to the inventory";
	introductions[4] = "                        These reports include:";
	introductions[5] = "1 - An Inventory List";
	introductions[6] = "    A list of all information on all books in inventory";
	introductions[7] = "2 - An Inventory  Wholesale  Value List";
	introductions[8] = "    A list of the wholesale value of all books in inventory";
	introductions[9] = "    and the total wholesale value of all books";
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

