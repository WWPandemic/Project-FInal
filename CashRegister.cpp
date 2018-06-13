#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <string>
#include "CashRegister.h"

//**************************
//* Constructor definition *
//**************************

CashRegister::CashRegister(Bundle b)
{
	menuBooks = b;
	chosenOption = 4;

	totalSales = 0.0;
	totalTax = 0.0;
	totalProfit = 0.0;
	transactions = 0;
	booksSold = 0;

	std::cout << "Starting up Cash Register module ...\n";
	setDate();
	setBalance();

	introductions[0] = "---------------------------------------------------------------------------";
	introductions[1] = "                      Welcome to the Cashier module:";
	introductions[2] = "";
	introductions[3] = "";
	introductions[4] = "1 - Start a new transaction";
	introductions[5] = "    Look up and process items for a new customer";
	introductions[6] = "2 - Process a refunded item";
	introductions[7] = "    Add an item back into stock and refund money";
	introductions[8] = "3 - Print a sales report";
	introductions[9] = "    Lists sales, profit and tax details";
	introductions[10] = "4 - Go back to the main menu";
	introductions[11] = "";
	introductions[12] = "---------------------------------------------------------------------------";
	usedIntroLines = 13;
}

//***********************
//* Mutator definitions *
//***********************

void CashRegister::setDate()						// Set current date
{
	int m, d, y;
	std::cout << "Please enter today's date (MM DD YYYY): ";			// Needs validation
	std::cin >> m >> d >> y;
	currentDate.setDate(m, d, y);
}

void CashRegister::setBalance()						// Set balance
{
	int bal;
	std::cout << "Please enter amount of money in cash register: $";		// Needs validation
	std::cin >> bal;
	balance = bal;
}

void CashRegister::addBalance(double b)						// Add amount to balance
{
	balance += b;
}

void CashRegister::addSales(double s)				// Add amount to totalSales
{
	totalSales += s;
}

void CashRegister::addTax(double t)					// Add amount to totalTax
{
	totalTax += t;
}

void CashRegister::addProfit(double p)				// Add amount to totalProfit
{
	totalProfit += p;
}

void CashRegister::addTransaction()					// Add one to transactions
{
	transactions++;
}

void CashRegister::addBookSold(int b)					// Add amount to booksSold
{
	booksSold += b;
}

void CashRegister::refundMoney(Book *b)				// Reduce book amounts from register
{
	double retailPrice = b->getRetailPrice();
	balance -= retailPrice + (retailPrice * (TAX_RATE / 100));
	totalSales -= retailPrice + (retailPrice * (TAX_RATE / 100));
	totalTax -= retailPrice * (TAX_RATE / 100);
	totalProfit -= retailPrice - b->getWholesaleCost();
	booksSold--;
	std::cout << std::setprecision(2) << std::fixed;
	std::cout << "$" << retailPrice + (retailPrice * (TAX_RATE / 100)) << " refunded.\n";
}

//************************
//* Function definitions *
//************************

std::string CashRegister::getDate()			// Return date as string
{
	return currentDate.toString();
}

void CashRegister::newTransaction(Bundle b)		// Create a new transaction
{
	ShoppingCart cart(b);

	if (cart.getComplete())
	{
		processCart(cart);
		reduceStock(b, cart);
		printReceipt(cart);
	}
}

void CashRegister::processCart(ShoppingCart c)		// Add cart values to register
{
	addBalance(c.getTotalCost());
	addSales(c.getTotalCost());
	addProfit(c.getTotalProfit());
	addTax(c.getTax());
	addBookSold(c.getSize());
	transactions++;
}

void CashRegister::reduceStock(Bundle b, ShoppingCart c)	// Adjust inventory based on purchases
{
	Book *bundle = b.getBundle();
	Book *cart = c.getBundle();
	
	for (int i = 0; i < c.getSize(); i++)		// repeat for every book in cart
	{
		for (int j = 0; j < b.getSize(); j++) {		// linear search bundle
			if (*(bundle + j) == *(cart + i)) {
				(bundle + j)->setQuantityOnHand(((bundle + j)->getQuantityOnHand() - 1));
			}
		}
	}
}

void CashRegister::refundBook(Bundle b)					// Refund a book
{
	std::string repeat = "";
	std::cout << "Please enter Book ISBN to refund.\n";
	do {
		int userISBN;
		std::cout << "ISBN: ";
		std::cin >> userISBN;

		// Search mainbundle for userISBN
		int pos = searchISBN(b, userISBN);	
		if (pos >= 0) {
			Book *currentSearch = b.getBundle();
			std::cout << "\n";
			(currentSearch + pos)->print();		// print details of book
			std::cout << "\n";

			// confirm refund
			std::string confirm = "";
			std::cout << "Refund this book? (y/n): ";
			getline(std::cin, confirm);
			if (confirm == "y" || confirm == "Y") {
				(currentSearch + pos)->setQuantityOnHand(((currentSearch + pos)->getQuantityOnHand() + 1));	// add 1 to stock
				refundMoney((currentSearch + pos));
			}
			std::cout << "\n\n";
		}
		else {
			std::cout << "Could not find specified book!\n\n";
		}

		// Prompt for another search
		std::cout << "Refund another item? (y/n): ";
		getline(std::cin, repeat);
	} while (repeat == "y" || repeat == "Y");
}

void CashRegister::sortISBN(Bundle b)				// Sort main bundle by isbn
{
	Book *bundle = b.getBundle();
	double total = 0;

	for (int ind = 0; ind < b.getSize(); ind++)
	{
		int minISBN = (*bundle).getISBN();
		int swapInd = ind;
		for (int target = ind; target < b.getSize(); target++)
		{
			if ((*bundle).getISBN() < minISBN)
			{
				swapInd = target;
				minISBN = (*bundle).getISBN();
			}
		}
		if (swapInd != ind)
		{
			Book temp = *(bundle + ind);
			*(bundle + ind) = *(bundle + swapInd);
			*(bundle + swapInd) = temp;
		}
	}
}

int CashRegister::searchISBN(Bundle b, int search)		// Search main bundle for isbn, returns index position or -1
{
	Book *bundle = b.getBundle();
	int first = 0;
	int last = b.getSize();
	int mid = 0;

	sortISBN(b);

	while (first <= last) {
		mid = (first + last) / 2;
		if ((bundle + mid)->getISBN() == search) {
			return mid;		// If found, return index
		}
		else {
			if ((bundle + mid)->getISBN() > search) {
				last = mid - 1;
			}
			else {
				first = mid + 1;
			}
		}
	}

	// If not found, return -1
	mid = -1;
	return mid;
}

void CashRegister::printReceipt(ShoppingCart c)			// Print details of current transaction
{
	printLines(50);
	std::cout << std::setw(44) << "Serendipity Booksellers Order Summary" << std::endl;
	std::cout << std::setw(30) << currentDate.toString() << std::endl;
	printLines(50);
	c.printAll();
	printLines(50);
	std::cout << std::setprecision(2) << std::fixed;
	std::cout << std::setw(40) << std::left << "Subtotal:" << c.getSubtotal() << std::endl;
	std::cout << std::setw(40) << std::left << "Tax:" << c.getTax() << std::endl;
	std::cout << std::setw(40) << std::left << "Total:" << c.getTotalCost() << std::endl << std::endl;
	std::cout << std::setw(40) << std::left << "Amount Paid:" << c.getAmountPaid() << std::endl;
	std::cout << std::setw(40) << std::left << "Change:" << c.getChange() << std::endl;
	printLines(50);
}

void CashRegister::printSalesReport()					// Print sales report of cash register
{
	printLines(50);
	std::cout << std::setw(43) << "Serendipity Booksellers Sales Report" << std::endl;
	std::cout << std::setw(30) << currentDate.toString() << std::endl;
	printLines(50);
	std::cout << std::setprecision(2) << std::fixed << std::endl;
	std::cout << std::setw(40) << std::left << "Register Balance:" << balance << std::endl;
	std::cout << std::setw(40) << std::left << "Total Sales:" << totalSales << std::endl;
	std::cout << std::setw(40) << std::left << "Total Tax:" << totalTax << std::endl;
	std::cout << std::setw(40) << std::left << "Total Profit:" << totalProfit << std::endl;
	std::cout << std::setw(40) << std::left << "Number of Transactions:" << transactions << std::endl;
	std::cout << std::setw(40) << std::left << "Number of Books Sold:" << booksSold << std::endl << std::endl;
	printLines(50);
}

void CashRegister::printLines(int l)					// Print lines for formatting
{
	for (int i = 0; i < l; i++) {
		std::cout << "-";
	}
	std::cout << std::endl;
}

//********************
//* Menu definitions *
//********************

void CashRegister::getInput()
{
	do
	{
		std::cout << "What would you like to do?" << std::endl;
		std::string input;
		getline(std::cin, input);
		chosenOption = std::stoi(input);
	} while (chosenOption < 0 || chosenOption > 4);
}

void CashRegister::runOptions()
{
	switch (chosenOption)
	{
	case 1:
		newTransaction(menuBooks);
		break;
	case 2:
		refundBook(menuBooks);
		break;
	case 3:
		printSalesReport();
		break;
	case 4:
	default:
		isUsingMenu = false;
		break;
	}
}

/*
To do:
- isbn search/sort
- input validation

- possible feature: save receipts to output file
*/