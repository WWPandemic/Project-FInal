#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <string>
#include "CashRegister.h"

//**************************
//* Constructor definition *
//**************************

CashRegister::CashRegister(Bundle &b)
{
	menuBooks = b;
	chosenOption = 4;

	totalSales = 0.0;
	totalTax = 0.0;
	totalProfit = 0.0;
	transactions = 0;
	booksSold = 0;

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

	setUpRegister();
}

//***********************
//* Mutator definitions *
//***********************

// Set date and balance
void CashRegister::setUpRegister()
{
	clearScreen();
	std::cout << "Starting up Cash Register module ...\n\n";
	int m, d, y;
	double bal;
	std::string input;

	do {
		std::cout << "Please enter today's date (MMDDYYYY): ";
		getline(std::cin, input);
		try {
			m = stoi(input.substr(0, 2));
			d = stoi(input.substr(2, 2));
			y = stoi(input.substr(4, 4));
		}
		catch (...) {
			y = 0;
		}
		if (y == 0 || y < 2000) {
			std::cout << "Invalid date.\n\n";
		}
	} while (y == 0 || y < 2000);

	do {
		std::cout << "Please enter amount of money in cash register: $";
		getline(std::cin, input);
		try {
			bal = stod(input);
		}
		catch (...) {
			bal = -1;
		}
		if (bal == -1) {
			std::cout << "Invalid amount.\n\n";
		}
	} while (bal == -1);

	clearScreen();

	currentDate = Date(m, d, y);
	balance = bal;
}

// Add amount to balance
void CashRegister::addBalance(double b)
{
	balance += b;
}

// Add amount to totalSales
void CashRegister::addSales(double s)
{
	totalSales += s;
}

// Add amount to totalTax
void CashRegister::addTax(double t)
{
	totalTax += t;
}

// Add amount to totalProfit
void CashRegister::addProfit(double p)
{
	totalProfit += p;
}

// Add one to transactions
void CashRegister::addTransaction()
{
	transactions++;
}

// Add amount to booksSold
void CashRegister::addBookSold(int b)
{
	booksSold += b;
}

// Reduce book amounts from register
void CashRegister::refundMoney(Book b)
{
	double retailPrice = b.getPrice();
	balance -= retailPrice + (retailPrice * (TAX_RATE / 100));
	totalSales -= retailPrice + (retailPrice * (TAX_RATE / 100));
	totalTax -= retailPrice * (TAX_RATE / 100);
	totalProfit -= retailPrice - b.getCost();
	booksSold--;
}

//************************
//* Function definitions *
//************************

// Return date as string
std::string CashRegister::getDate()
{
	return currentDate.toString();
}

// Create a new transaction
void CashRegister::newTransaction(Bundle &b)
{
	clearScreen();
	std::cout << "---------------------------------------------------------------------------\n";
	printCenter("New Transaction");
	std::cout << "---------------------------------------------------------------------------\n\n";

	// Create cart
	ShoppingCart cart(b);

	// If cart is successfully completed
	if (cart.getComplete())
	{
		// Add cart values to register
		processCart(cart);

		// Reduce inventory stock from bought items
		reduceStock(b, cart);

		// Print receipt
		std::cout << "Press <Enter> to Print Receipt ...";
		std::string pause = getConfirmation();
		printReceipt(cart);
	}
	clearScreen();
}

// Add cart values to register
void CashRegister::processCart(ShoppingCart c)		
{
	addBalance(c.getTotalCost());
	addSales(c.getTotalCost());
	addProfit(c.getTotalProfit());
	addTax(c.getTax());
	addBookSold(c.getSize());
	transactions++;
}

// Adjust inventory based on purchases
void CashRegister::reduceStock(Bundle &b, ShoppingCart c)	
{	
	for (int cartBook = 0; cartBook < c.getSize(); cartBook++)		// repeat for every book in cart
	{
		int pos = findIndex(b, c[cartBook]);

		if (pos >= 0) {
			b[pos].setQuantity(b[pos].getQuantity() - 1);
		}
	}

}

// Add book back to inventory from refund
void CashRegister::increaseStock(Bundle &b, Book book) 
{
	int pos = findIndex(b, book);

	if (pos >= 0) {
		b[pos].setQuantity(b[pos].getQuantity() + 1);
	}
}

int CashRegister::findIndex(const Bundle &b, Book search) {
	int first = 0;
	int last = b.getSize();
	int mid = 0;

	while (first <= last) {
		mid = (first + last) / 2;
		if (b[mid].getISBN() == search.getISBN()) {
			return mid;		// If found, return index
		}
		else {
			if (b[mid].getISBN() > search.getISBN()) {
				last = mid - 1;
			}
			else {
				first = mid + 1;
			}
		}
	}
	std::cout << "not found, returning ...\n";
	return mid;
}

// Refund a book
void CashRegister::refundBook(Bundle &b)					
{
	clearScreen();
	std::cout << "---------------------------------------------------------------------------\n";
	printCenter("Book Refund");
	std::cout << "---------------------------------------------------------------------------\n\n";

	std::string repeat;		// To loop refunding of books

	// Sort bundle by ISBN for searchability
	sortISBN(b);

	std::cout << "Please enter Book ISBN to process refund.\n";
	do {
		// Prompt user for ISBN
		int userISBN;
		std::cout << "ISBN: ";
		std::string input;
		getline(std::cin, input);
		// Check for invalid inputs
		try {
			userISBN = std::stoi(input);
		}
		catch (...)
		{
			userISBN = 0;
		}
		std::cout << std::endl;

		// Search mainbundle for userISBN
		int pos = searchISBN(b, userISBN);	

		// If book was found
		if (pos >= 0) {
			// Print book details
			std::cout << "---------------------------------------------------------------------------\n\n";
			printBook(b[pos]);
			std::cout << "---------------------------------------------------------------------------\n";

			// Prompt user for confirmation to refund
			std::cout << "Refund this book? (y/n): ";
			std::string confirm = getConfirmation();
			std::cout << std::endl;

			// If refund is confirmed
			if (confirm == "y" || confirm == "Y") {
				// If balance is less than refund
				if (balance < b[pos].getPrice() + (b[pos].getPrice() * (TAX_RATE / 100))) {
					std::cout << "Not enough money in register, refund cancelled.\n";
				}
				else {
					// Add 1 to book stock
					increaseStock(b, b[pos]);
					// Reduce values in register
					refundMoney(b[pos]);
					// Print confirmation
					std::cout << std::setprecision(2) << std::fixed;
					std::cout << "$" << b[pos].getPrice() + (b[pos].getPrice() * (TAX_RATE / 100)) << " was refunded.\n\n";
				}
			}
			// If refund is not confirmed
			else {
				std::cout << "Refund cancelled.\n\n";
			}
		}
		// If book was not found
		else {
			std::cout << "Could not find specified book!\n\n";
		}

		// Prompt user for another refund
		std::cout << "Refund another item? (y/n): ";
		repeat = getConfirmation();
	} while (repeat == "y" || repeat == "Y");
	clearScreen();
}

// Sort main bundle by isbn
void CashRegister::sortISBN(Bundle &b)				
{
	for (int ind = 0; ind < b.getSize(); ind++)
	{
		int minISBN = b[ind].getISBN();
		int swapInd = ind;
		for (int target = ind; target < b.getSize(); target++)
		{
			if (b[target].getISBN() < minISBN)
			{
				swapInd = target;
				minISBN = b[target].getISBN();
			}
		}
		if (swapInd != ind)
		{
			b.getArray().swap(b[ind], b[swapInd]);
		}
	}
}

// Search main bundle for isbn, returns index position or -1
int CashRegister::searchISBN(Bundle &b, int search)		
{
	int first = 0;
	int last = b.getSize();
	int mid = 0;

	while (first <= last) {
		mid = (first + last) / 2;
		if (b[mid].getISBN() == search) {
			return mid;		// If found, return index
		}
		else {
			if (b[mid].getISBN() > search) {
				last = mid - 1;
			}
			else {
				first = mid + 1;
			}
		}
	}

	// If not found, return -1
	return -1;
}

// Print book details
void CashRegister::printBook(Book book) {
	std::cout << std::setprecision(2) << std::fixed;
	std::cout << book.getTitle() << std::endl;
	std::cout << "by " << std::setw(57) << std::left << book.getAuthor() << "$" << book.getPrice() << std::endl;
	std::cout << std::endl;
}


// Print details of current transaction
void CashRegister::printReceipt(ShoppingCart c)			
{
	clearScreen();
	std::cout << "---------------------------------------------------------------------------\n";
	printCenter("Serendipity Booksellers Order Summary");
	printCenter(currentDate.toString());
	std::cout << "---------------------------------------------------------------------------\n\n";
	c.printAll();
	std::cout << "---------------------------------------------------------------------------\n\n";
	std::cout << std::setprecision(2) << std::fixed;
	std::cout << std::setw(60) << std::left << "Subtotal:" << "$" << c.getSubtotal() << std::endl;
	std::cout << std::setw(60) << std::left << "Tax:" << "$" << c.getTax() << std::endl;
	std::cout << std::setw(60) << std::left << "Total:" << "$" << c.getTotalCost() << std::endl << std::endl;
	std::cout << std::setw(60) << std::left << "Amount Paid:" << "$" << c.getAmountPaid() << std::endl;
	std::cout << std::setw(60) << std::left << "Change:" << "$" << c.getChange() << std::endl << std::endl;
	std::cout << "---------------------------------------------------------------------------\n";

	std::cout << "\n\n";
	std::cout << "Press <Enter> to Continue ...";
	std::string pause = getConfirmation();
	clearScreen();
}

// Print sales report of cash register
void CashRegister::printSalesReport()					
{
	std::cout << "---------------------------------------------------------------------------\n";
	printCenter("Serendipity Booksellers Sales Report");
	printCenter(currentDate.toString());
	std::cout << "---------------------------------------------------------------------------\n";
	std::cout << std::setprecision(2) << std::fixed << std::endl;
	std::cout << std::setw(60) << std::left << "Register Balance:" << "$" << balance << std::endl;
	std::cout << std::setw(60) << std::left << "Total Sales:" << "$" << totalSales << std::endl;
	std::cout << std::setw(60) << std::left << "Total Tax:" << "$" << totalTax << std::endl;
	std::cout << std::setw(60) << std::left << "Total Profit:" << "$" << totalProfit << std::endl;
	std::cout << std::setw(60) << std::left << "Number of Transactions:" << transactions << std::endl;
	std::cout << std::setw(60) << std::left << "Number of Books Sold:" << booksSold << std::endl << std::endl;
	std::cout << "---------------------------------------------------------------------------\n";

	std::cout << "\n\n";
	std::cout << "Press <Enter> to Continue ...";
	std::string pause = getConfirmation();
	clearScreen();
}

// Print center text in between line breaks
void CashRegister::printCenter(std::string text) {
	int lineLength = 76;
	int spacing = (lineLength / 2) + (text.length() / 2);
	std::cout << std::setw(spacing) << std::right << text << std::endl;
}

// Clear text from console
void CashRegister::clearScreen()
{
	system("CLS");
}

// Get confirmation
std::string CashRegister::getConfirmation() {
	std::string input;
	getline(std::cin, input);
	return input;
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