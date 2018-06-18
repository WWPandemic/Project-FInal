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
	int m, d, y, bal;
	std::cout << "Please enter today's date (MM DD YYYY): ";
	std::cin >> m >> d >> y;
	std::cout << "Please enter amount of money in cash register: $";
	std::cin >> bal;
	std::cin.ignore();
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
}

// Add cart values to register
void CashRegister::processCart(ShoppingCart c)		
{
	addBalance(c.getTotalCost());
	addSales(c.getTotalCost());
	addProfit(c.getTotalProfit());
	addTax(c.getTax());
	addBookSold(c.getLength());
	transactions++;
}

// Adjust inventory based on purchases************
void CashRegister::reduceStock(Bundle &b, ShoppingCart c)	
{	
	for (int i = 0; i < c.getLength(); i++)		// repeat for every book in cart
	{
		for (int j = 0; j < b.getLength(); j++) {		// linear search bundle
			if (b[j] == c[i]) {
				b[j].setQuantity(b[j].getQuantity() - 1);
			}
		}
	}
}

// Refund a book
void CashRegister::refundBook(Bundle &b)					
{
	clearScreen();
	std::cout << "---------------------------------------------------------------------------\n";
	printCenter("Book Refund");
	std::cout << "---------------------------------------------------------------------------\n\n";

	std::string repeat;
	std::cout << "Please enter Book ISBN to process refund.\n";
	do {
		int userISBN;
		std::cout << "ISBN: ";
		std::cin >> userISBN;
		std::cin.ignore();
		std::cout << std::endl;

		// Search mainbundle for userISBN
		int pos = searchISBN(b, userISBN);	
		if (pos >= 0) {
			// Print book details
			printBook(b[pos]);

			// Ask to confirm refund
			std::cout << "Refund this book? (y/n): ";
			std::string confirm = getConfirmation();
			std::cout << std::endl;

			if (confirm == "y" || confirm == "Y") {
				// Add 1 to book stock
				b[pos].setQuantity((b[pos].getQuantity() + 1));
				// Reduce values in register
				refundMoney(b[pos]);
				//Print confirmation
				std::cout << std::setprecision(2) << std::fixed;
				std::cout << "$" << b[pos].getPrice() + (b[pos].getPrice() * (TAX_RATE / 100)) << " was refunded.\n\n";
			}
		}
		else {
			std::cout << "Could not find specified book!\n\n";
		}

		// Prompt for another search
		std::cout << "Refund another item? (y/n): ";
		repeat = getConfirmation();
	} while (repeat == "y" || repeat == "Y");
}

// Sort main bundle by isbn
Bundle CashRegister::sortISBN(Bundle b)				
{
	for (int ind = 0; ind < b.getLength(); ind++)
	{
		int minISBN = b[ind].getISBN();
		int swapInd = ind;
		for (int target = ind; target < b.getLength(); target++)
		{
			if (b[ind].getISBN() < minISBN)
			{
				swapInd = target;
				minISBN = b[ind].getISBN();
			}
		}
		if (swapInd != ind)
		{
			b.getArray().swap(b[ind], b[swapInd]);
		}
	}

	return b;
}

// Search main bundle for isbn, returns index position or -1
int CashRegister::searchISBN(Bundle b, int search)		
{
	int first = 0;
	int last = b.getLength();
	int mid = 0;

	Bundle sorted = sortISBN(b);

	while (first <= last) {
		mid = (first + last) / 2;
		if (sorted[mid].getISBN() == search) {
			return mid;		// If found, return index
		}
		else {
			if (sorted[mid].getISBN() > search) {
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
	std::cout << "by " << std::setw(50) << std::left << book.getAuthor() << "$" << book.getPrice() << std::endl;
	std::cout << std::endl;
}


// Print details of current transaction
void CashRegister::printReceipt(ShoppingCart c)			
{
	clearScreen();
	std::cout << "---------------------------------------------------------------------------\n";
	printCenter("Serendipity Booksellers Order Summary");
	printCenter(currentDate.toString());
	std::cout << "---------------------------------------------------------------------------\n";
	c.printAll();
	std::cout << "---------------------------------------------------------------------------\n";
	std::cout << std::setprecision(2) << std::fixed;
	std::cout << std::setw(50) << std::left << "Subtotal:" << c.getSubtotal() << std::endl;
	std::cout << std::setw(50) << std::left << "Tax:" << c.getTax() << std::endl;
	std::cout << std::setw(50) << std::left << "Total:" << c.getTotalCost() << std::endl << std::endl;
	std::cout << std::setw(50) << std::left << "Amount Paid:" << c.getAmountPaid() << std::endl;
	std::cout << std::setw(50) << std::left << "Change:" << c.getChange() << std::endl;
	std::cout << "---------------------------------------------------------------------------\n";
}

// Print sales report of cash register
void CashRegister::printSalesReport()					
{
	clearScreen();
	std::cout << "---------------------------------------------------------------------------\n";
	printCenter("Serendipity Booksellers Sales Report");
	printCenter(currentDate.toString());
	std::cout << "---------------------------------------------------------------------------\n";
	std::cout << std::setprecision(2) << std::fixed << std::endl;
	std::cout << std::setw(50) << std::left << "Register Balance:" << balance << std::endl;
	std::cout << std::setw(50) << std::left << "Total Sales:" << totalSales << std::endl;
	std::cout << std::setw(50) << std::left << "Total Tax:" << totalTax << std::endl;
	std::cout << std::setw(50) << std::left << "Total Profit:" << totalProfit << std::endl;
	std::cout << std::setw(50) << std::left << "Number of Transactions:" << transactions << std::endl;
	std::cout << std::setw(50) << std::left << "Number of Books Sold:" << booksSold << std::endl << std::endl;
	std::cout << "---------------------------------------------------------------------------\n";

	std::cout << "\n\n\n";
	std::cout << "Press <Enter> to Continue ...";
	std::string pause = getConfirmation();
	clearScreen();
}

// Print center text in between line breaks
void CashRegister::printCenter(std::string text) {
	int lineLength = 76;
	int spacing = (lineLength / 2) + (text.length() / 2);
	std::cout << std::setw(spacing) << text << std::endl;
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