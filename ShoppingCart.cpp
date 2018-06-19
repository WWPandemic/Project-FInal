#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include "ShoppingCart.h"

/*
Constructor:	ShoppingCart
Author:			Terry Chiem
Parameters:		Bundle *b - A pointer to a reference of the main bundle
Returns:		ShoppingCart object
Description:	This constructor creates a ShoppingCart which then
				allows the user to add books to it. After the addition
				process is finished, all of the values are calculated
				and assigned to the variables.
*/
ShoppingCart::ShoppingCart(Bundle *b)
{
	subtotal = 0.0;
	totalCost = 0.0;
	totalProfit = 0.0;
	amountPaid = 0.0;
	change = 0.0;

	addItems(b);
	processTotals();
	processPay();
	calculateChange();
	validateCart();
}
/*
Function:		getSubtotal
Author :		Terry Chiem
Parameters :	none
Returns :		double
Description :	An accessor for subtotal
*/
double ShoppingCart::getSubtotal() const		
{
	return subtotal;
}
/*
Function:		getTotalCost
Author :		Terry Chiem
Parameters :	none
Returns :		double
Description :	An accessor for totalCost
*/
double ShoppingCart::getTotalCost() const		
{
	return totalCost;
}
/*
Function:		getTotalProfit
Author :		Terry Chiem
Parameters :	none
Returns :		double
Description :	An accessor for totalProfit
*/
double ShoppingCart::getTotalProfit() const	
{
	return totalProfit;
}
/*
Function:		getAmountPaid
Author :		Terry Chiem
Parameters :	none
Returns :		double
Description :	An accessor for amountPaid
*/
double ShoppingCart::getAmountPaid() const	
{
	return amountPaid;
}
/*
Function:		getChange
Author :		Terry Chiem
Parameters :	none
Returns :		double
Description :	An accessor for change
*/
double ShoppingCart::getChange() const	
{
	return change;
}
/*
Function:		getComplete
Author :		Terry Chiem
Parameters :	none
Returns :		bool
Description :	An accessor for completeCart
*/
bool ShoppingCart::getComplete() const
{
	return completeCart;
}
/*
Function:		getTax
Author :		Terry Chiem
Parameters :	none
Returns :		double
Description :	Calculates the tax by multiplying the
				subtotal with the tax rate.
*/
double ShoppingCart::getTax() const		
{
	return subtotal * (TAX_RATE/100);
}
/*
Function:		addSubtotal
Author :		Terry Chiem
Parameters :	double
Returns :		none
Description :	Adds the amount to subtotal.
*/
void ShoppingCart::addSubtotal(double c)			
{
	subtotal += c;
}
/*
Function:		addTotalProfit
Author :		Terry Chiem
Parameters :	double
Returns :		none
Description :	Adds the amount to totalProfit.
*/
void ShoppingCart::addTotalProfit(double p)			
{
	totalProfit += p;
}
/*
Function:		calculateTotal
Author :		Terry Chiem
Parameters :	none
Returns :		none
Description :	Calculates totalCost by adding the subtotal
				with the tax owed.
*/
void ShoppingCart::calculateTotal()					
{
	totalCost = subtotal + getTax();
}
/*
Function:		calculateChange
Author :		Terry Chiem
Parameters :	none
Returns :		none
Description :	Calculates change by subtracting the total
				cost from the amount paid.
*/
void ShoppingCart::calculateChange()				
{
	change = amountPaid - totalCost;
}
/*
Function:		processPay
Author :		Terry Chiem
Parameters :	none
Returns :		none
Description :	Prompts the user to enter the amount the customer paid. 
				Amount is assigned to amountPaid.
*/
void ShoppingCart::processPay()						
{
	// If there are no items in cart
	if (getTotalCost() == 0) {
		std::cout << "No items were added, returning to menu ...\n";
	}
	// If there are items in cart
	else {
		std::string repeat;
		double paid;
		std::cout << std::setprecision(2) << std::fixed;
		std::cout << "The total is: $" << getTotalCost() << std::endl;
		
		do {
			// Prompt user to enter amount paid
			std::cout << "\nEnter the amount paid: $";
			std::string input;
			getline(std::cin, input);
			// Check for invalid inputs
			try {
				paid = std::stod(input);
			}
			catch (...)
			{
				paid = -1;
			}
			if (paid < 0) {
				std::cout << "Invalid amount.\n";
				repeat = "y";
			}
			// If amount paid is less than total cost
			if (paid > -1 && paid < getTotalCost()) {
				std::cout << "Amount paid is lesser than amount owed, enter amount paid again? (y/n): ";
				getline(std::cin, repeat);
			}
			// If amount paid is valid, exit loop
			if (paid >= getTotalCost()) {
				repeat = "n";
			}
		} while (repeat == "y" || repeat == "Y");

		std::cout << std::endl;
		amountPaid = paid;
	}
}
/*
Function:		getConfirmation
Author :		Terry Chiem
Parameters :	none
Returns :		string
Description :	Gets the next input and returns it as a string.
*/
std::string ShoppingCart::getConfirmation() {
	std::string input;
	getline(std::cin, input);
	return input;
}
/*
Function:		addItems
Author :		Terry Chiem
Parameters :	Bundle *b - A pointer to a reference of the main bundle
Returns :		none
Description :	Prompts the user for book ISBNs to add to the current cart.
*/
void ShoppingCart::addItems(Bundle *b) {
	int count = 0;			// Number of books in cart
	std::string repeat;		// To loop adding of books

	// Sort bundle by ISBN for searchability
	Bundle sorted = sortISBN(b);

	std::cout << "Please enter Book ISBNs to add items to the cart.\n";
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

		// Search sorted bundle for userISBN
		int pos = searchISBN(sorted, userISBN);

		// If book is found
		if (pos >= 0) {
			// Print book details
			std::cout << "\n---------------------------------------------------------------------------\n\n";
			printBook(sorted[pos]);
			std::cout << "Stock: " << sorted[pos].getQuantity() << std::endl;
			std::cout << "---------------------------------------------------------------------------\n";

			// Prompt user for confirmation to add to cart
			std::cout << "\nAdd this item to cart? (y/n): ";
			std::string confirm = getConfirmation();

			// If add is confirmed
			if (confirm == "y" || confirm == "Y") {
				// If item is in stock
				if (sorted[pos].getQuantity() > 0) {
					// Add book to cart
					addBook(sorted[pos]);
					std::cout << "'" << sorted[pos].getTitle() << "' added to cart.\n\n";

					// Check cart size
					ensureSize(++count);
				}
				// If item is out of stock
				else {
					std::cout << "Book is out of stock!\n\n";
				}
			}
			// If add is not confirmed
			else {
				std::cout << "Book was not added to cart.\n\n";
			}
		}
		// If book is not found
		else {
			std::cout << "\nCould not find specified book!\n\n";
		}

		// Prompt user to add another item
		std::cout << "\nAdd another item? (y/n): ";
		repeat = getConfirmation();
		std::cout << std::endl;
	} while (repeat == "y" || repeat == "Y");
}
/*
Function:		sortISBN
Author :		Terry Chiem
Parameters :	Bundle *b - A pointer to a reference of the main bundle
Returns :		Bundle
Description :	Performs a selective sort by ISBN on the main bundle and
				returns a copy of it.
*/
Bundle ShoppingCart::sortISBN(Bundle *b)
{
	Bundle sorted = *b;
	// Perform a selective sort by ISBN
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
int ShoppingCart::searchISBN(Bundle b, int search)
{
	int first = 0;
	int last = b.getSize();
	int mid = 0;
	// Perform a binary search for item
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
Function:		processTotals
Author :		Terry Chiem
Parameters :	none
Returns :		none
Description :	Goes through every book in the cart and adds its
				values to the member variables.
*/
void ShoppingCart::processTotals()		
{
	for (int i = 0; i < getSize(); i++) {
		addSubtotal(m_books[i].getPrice());
		addTotalProfit(m_books[i].getPrice() - m_books[i].getCost());
	}
	calculateTotal();
}
/*
Function:		validateCart
Author :		Terry Chiem
Parameters :	none
Returns :		none
Description :	Determines if the cart is valid. If the cart is not
				empty and paid off, sets the status to true and false
				otherwise.
*/
void ShoppingCart::validateCart()		
{
	if (getSize() > 0 && amountPaid >= totalCost) {
		completeCart = true;
	}
	else {
		completeCart = false;
	}
}
/*
Function:		printBook
Author :		Terry Chiem
Parameters :	Book book - Item to be printed
Returns :		none
Description :	Prints out the book's details (title, author, price).
*/
void ShoppingCart::printBook(Book book) {
	std::cout << std::setprecision(2) << std::fixed;
	std::cout << book.getTitle() << std::endl;
	std::cout << "by " << std::setw(57) << std::left << book.getAuthor() << "$" << book.getPrice() << std::endl;
	std::cout << std::endl;
}
/*
Function:		printAll
Author :		Terry Chiem
Parameters :	none
Returns :		none
Description :	Prints out every book in cart.
*/
void ShoppingCart::printAll() {
	for (int i = 0; i < getSize(); i++)
	{
		std::cout << "Item #" << i + 1 << std::endl;
		printBook(m_books[i]);
	}
}