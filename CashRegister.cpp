#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <string>
#include "CashRegister.h"

/*
Constructor:	CashRegister
Author:			Terry Chiem
Parameters:		Bundle &b - A reference to the bundle created from BookReader
Returns:		CashRegister object
Description:	This constructor creates a CashRegister object which allows
				the user to navigate a menu to access its functions.
*/
CashRegister::CashRegister(Bundle &b)
{
	bPtr = &b;
	chosenOption = 4;
	totalSales = 0.0;
	totalTax = 0.0;
	totalProfit = 0.0;
	transactions = 0;
	booksSold = 0;
	setUpRegister();

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
	introductions[12] = "";
	introductions[13] = "---------------------------------------------------------------------------";
	usedIntroLines = 14;
}
/*
Function:		setUpRegister
Author :		Terry Chiem
Parameters :	none
Returns :		none
Description :	Prompts user to enter date and register balance then
				initializes those variables.
*/
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
/*
Function:		addBalance
Author :		Terry Chiem
Parameters :	double b
Returns :		none
Description :	Adds the amount to balance.
*/
void CashRegister::addBalance(double b)
{
	balance += b;
}
/*
Function:		addSales
Author :		Terry Chiem
Parameters :	double s
Returns :		none
Description :	Adds the amount to totalSales.
*/
void CashRegister::addSales(double s)
{
	totalSales += s;
}
/*
Function:		addTax
Author :		Terry Chiem
Parameters :	double t
Returns :		none
Description :	Adds the amount to totalTax.
*/
void CashRegister::addTax(double t)
{
	totalTax += t;
}
/*
Function:		addProfit
Author :		Terry Chiem
Parameters :	double p
Returns :		none
Description :	Adds the amount to totalProfit.
*/
void CashRegister::addProfit(double p)
{
	totalProfit += p;
}
/*
Function:		addBooksSold
Author :		Terry Chiem
Parameters :	int b - Amount of books
Returns :		none
Description :	Adds the amount to booksSold.
*/
void CashRegister::addBookSold(int b)
{
	booksSold += b;
}
/*
Function:		refundMoney
Author :		Terry Chiem
Parameters :	Book b - Book to be refunded
Returns :		none
Description :	Reduces register values by the book's price.
*/
void CashRegister::refundMoney(Book b)
{
	double retailPrice = b.getPrice();
	balance -= retailPrice + (retailPrice * (TAX_RATE / 100));
	totalSales -= retailPrice + (retailPrice * (TAX_RATE / 100));
	totalTax -= retailPrice * (TAX_RATE / 100);
	totalProfit -= retailPrice - b.getCost();
	booksSold--;
}
/*
Function:		getConfirmation
Author :		Terry Chiem
Parameters :	none
Returns :		string
Description :	Gets the next input and returns it as a string.
*/
std::string CashRegister::getConfirmation() {
	std::string input;
	getline(std::cin, input);
	return input;
}
/*
Function:		getDate
Author :		Terry Chiem
Parameters :	none
Returns :		string
Description :	Returns the current date as a string.
*/
std::string CashRegister::getDate()
{
	return currentDate.toString();
}
/*
Function:		newTransaction
Author :		Terry Chiem
Parameters :	Bundle *b - A pointer to a reference of the main bundle
Returns :		none
Description :	Creates a new ShoppingCart where the user adds books and payment.
				If the transaction is complete, process the cart's values to the
				register, adjust inventory and print a receipt.
*/
void CashRegister::newTransaction(Bundle *b)
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
/*
Function:		processCart
Author :		Terry Chiem
Parameters :	ShoppingCart c - Completed cart from newTransaction
Returns :		none
Description :	Adjust register values based on the books in the cart.
*/
void CashRegister::processCart(ShoppingCart c)		
{
	addBalance(c.getTotalCost());
	addSales(c.getTotalCost());
	addProfit(c.getTotalProfit());
	addTax(c.getTax());
	addBookSold(c.getSize());
	transactions++;
}
/*
Function:		reduceStock
Author :		Terry Chiem
Parameters :	Bundle *b - A pointer to a reference of the main bundle
				ShoppingCart c - Completed cart from newTransaction
Returns :		none
Description :	Adjusts bundle quantities for each book in the cart.
*/
void CashRegister::reduceStock(Bundle *b, ShoppingCart c)
{
	for (int cartBook = 0; cartBook < c.getSize(); cartBook++)		// repeat for every book in cart
	{
		int pos = findIndex(b, c[cartBook]);

		if (pos >= 0) {
			b->setBookQuantity(pos, (b->getArray()[pos].getQuantity() - 1));
		}
	}
}
/*
Function:		increaseStock
Author :		Terry Chiem
Parameters :	Bundle *b - A pointer to a reference of the main bundle
				Book book - Book that was refunded
Returns :		none
Description :	Increases the quantity of the refunded book by one.
*/
void CashRegister::increaseStock(Bundle *b, Book book) 
{
	Array<Book> bp = b->getArray();
	int pos = findIndex(b, book);

	if (pos >= 0) {
		b->setBookQuantity(pos, (bp[pos].getQuantity() + 1));
	}
}
/*
Function:		findIndex
Author :		Terry Chiem
Parameters :	Bundle *b - A pointer to a reference of the main bundle
				Book search - Book search item
Returns :		int
Description :	Performs a binary search to locate the index position of search item.
*/
int CashRegister::findIndex(const Bundle *b, Book search) {
	Array<Book> bp = b->getArray();

	int first = 0;
	int last = b->getSize();
	int mid = 0;

	while (first <= last) {
		mid = (first + last) / 2;
		if (bp[mid] == search) {
			return mid;		// If found, return index
		}
		else {
			if (bp[mid] > search) {
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
/*
Function:		refundBook
Author :		Terry Chiem
Parameters :	Bundle *b - A pointer to a reference of the main bundle
Returns :		none
Description :	Prompts the user for book ISBN to add to refund.
*/
void CashRegister::refundBook(Bundle *b)					
{
	clearScreen();
	std::cout << "---------------------------------------------------------------------------\n";
	printCenter("Book Refund");
	std::cout << "---------------------------------------------------------------------------\n\n";

	std::string repeat;		// To loop refunding of books

	// Sort bundle by ISBN for searchability
	Bundle sorted = sortISBN(b);

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
		int pos = searchISBN(sorted, userISBN);	

		// If book was found
		if (pos >= 0) {
			// Print book details
			std::cout << "---------------------------------------------------------------------------\n\n";
			printBook(sorted[pos]);
			std::cout << "---------------------------------------------------------------------------\n";

			// Prompt user for confirmation to refund
			std::cout << "Refund this book? (y/n): ";
			std::string confirm = getConfirmation();
			std::cout << std::endl;

			// If refund is confirmed
			if (confirm == "y" || confirm == "Y") {
				// If balance is less than refund
				if (balance < sorted[pos].getPrice() + (sorted[pos].getPrice() * (TAX_RATE / 100))) {
					std::cout << "Not enough money in register, refund cancelled.\n";
				}
				else {
					// Add 1 to book stock
					increaseStock(b, sorted[pos]);
					// Reduce values in register
					refundMoney(sorted[pos]);
					// Print confirmation
					std::cout << std::setprecision(2) << std::fixed;
					std::cout << "$" << sorted[pos].getPrice() + (sorted[pos].getPrice() * (TAX_RATE / 100)) << " was refunded.\n\n";
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
/*
Function:		sortISBN
Author :		Terry Chiem
Parameters :	Bundle *b - A pointer to a reference of the main bundle
Returns :		Bundle
Description :	Performs a selective sort by ISBN on the main bundle and
				returns a copy of it.
*/
Bundle CashRegister::sortISBN(Bundle *b)
{
	Bundle sorted = *b;

	for (int ind = 0; ind < b->getSize(); ind++)
	{
		int minISBN = sorted[ind].getISBN();
		int swapInd = ind;
		for (int target = ind; target < b->getSize(); target++)
		{
			if (sorted[target].getISBN() < minISBN)
			{
				swapInd = target;
				minISBN = sorted[target].getISBN();
			}
		}
		if (swapInd != ind)
		{
			sorted.getArray().swap(sorted[ind], sorted[swapInd]);
		}
	}
	return sorted;
}
/*
Function:		searchISBN
Author :		Terry Chiem
Parameters :	Bundle *b - A pointer to a reference of the main bundle
				int search - The search item (ISBN) specified by the user
Returns :		int
Description :	Performs a binary search for the search item and returns
				its index position if found, a -1 if not found.
*/
int CashRegister::searchISBN(Bundle b, int search)		
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
/*
Function:		printBook
Author :		Terry Chiem
Parameters :	Book book - Item to be printed
Returns :		none
Description :	Prints out the book's details (title, author, price).
*/
void CashRegister::printBook(Book book) {
	std::cout << std::setprecision(2) << std::fixed;
	std::cout << book.getTitle() << std::endl;
	std::cout << "by " << std::setw(57) << std::left << book.getAuthor() << "$" << book.getPrice() << std::endl;
	std::cout << std::endl;
}
/*
Function:		printReceipt
Author :		Terry Chiem
Parameters :	ShoppingCart c - Completed cart from newTransaction
Returns :		none
Description :	Prints the details of the cart.
*/
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
/*
Function:		printSalesReport
Author :		Terry Chiem
Parameters :	none
Returns :		none
Description :	Prints the details of the register.
*/
void CashRegister::printSalesReport()					
{
	std::cout << "---------------------------------------------------------------------------\n";
	printCenter("Serendipity Booksellers Sales Report");
	printCenter(currentDate.toString());
	std::cout << "---------------------------------------------------------------------------\n";
	std::cout << std::setprecision(2) << std::fixed << std::endl;
	std::cout << std::setw(60) << std::left << "Register Balance:" << "$" << balance << std::endl;
	std::cout << std::setw(60) << std::left << "Total Sales:" << "$" << totalSales << std::endl;
	std::cout << std::setw(60) << std::left << "Total Tax Collected:" << "$" << totalTax << std::endl;
	std::cout << std::setw(60) << std::left << "Total Profit:" << "$" << totalProfit << std::endl;
	std::cout << std::setw(60) << std::left << "Number of Transactions:" << transactions << std::endl;
	std::cout << std::setw(60) << std::left << "Number of Books Sold:" << booksSold << std::endl << std::endl;
	std::cout << "---------------------------------------------------------------------------\n";

	std::cout << "\n\n";
	std::cout << "Press <Enter> to Continue ...";
	std::string pause = getConfirmation();
	clearScreen();
}
/*
Function:		printCenter
Author :		Terry Chiem
Parameters :	string text - Text to be printed
Returns :		none
Description :	Prints out the text centered based on the length of the line breaks.
*/
void CashRegister::printCenter(std::string text) {
	int lineLength = 76;
	int spacing = (lineLength / 2) + (text.length() / 2);
	std::cout << std::setw(spacing) << std::right << text << std::endl;
}
/*
Function:		clearScreen
Author :		Terry Chiem
Parameters :	none
Returns :		none
Description :	Clears the console.
*/
void CashRegister::clearScreen()
{
	system("CLS");
}
/*
Function:		getInput
Author :		Terry Chiem/Evren Keskin
Parameters :	none
Returns :		none
Description :	Runs a loop to get a menu choice from user.
*/
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
/*
Function:		runOptions
Author :		Terry Chiem/Evren Keskin
Parameters :	none
Returns :		none
Description :	Performs a menu function based on the user's chosen menu option.
*/
void CashRegister::runOptions()
{
	switch (chosenOption)
	{
	case 1:
		newTransaction(bPtr);
		break;
	case 2:
		refundBook(bPtr);
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
