#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include "ShoppingCart.h"

//**************************
//* Constructor definition *
//**************************

ShoppingCart::ShoppingCart()
{
	subtotal = 0.0;
	totalCost = 0.0;
	totalProfit = 0.0;
	amountPaid = 0.0;
	change = 0.0;
	completeCart = false;
}

ShoppingCart::ShoppingCart(Bundle &b)
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

//************************
//* Accessor definitions *
//************************

double ShoppingCart::getSubtotal() const		
{
	return subtotal;
}

double ShoppingCart::getTotalCost() const		
{
	return totalCost;
}

double ShoppingCart::getTotalProfit() const	
{
	return totalProfit;
}

double ShoppingCart::getAmountPaid() const	
{
	return amountPaid;
}

double ShoppingCart::getChange() const	
{
	return change;
}

bool ShoppingCart::getComplete() const
{
	return completeCart;
}

// Calculate and return tax amount
double ShoppingCart::getTax() const		
{
	return subtotal * (TAX_RATE/100);
}



//***********************
//* Mutator definitions *
//***********************

// Add amount to subtotal
void ShoppingCart::addSubtotal(double c)			
{
	subtotal += c;
}

// Add amount to totalProfit
void ShoppingCart::addTotalProfit(double p)			
{
	totalProfit += p;
}

// Calculate totalCost
void ShoppingCart::calculateTotal()					
{
	totalCost = subtotal + getTax();
}

// Calculate change
void ShoppingCart::calculateChange()				
{
	change = amountPaid - totalCost;
}

// Input value for amountPaid
void ShoppingCart::processPay()						
{
	// If there are no items in cart
	if (getTotalCost() == 0) {
		std::cout << "No items were added, returning to menu ...\n";
	}
	// If there are items in cart
	else {
		double paid;
		std::cout << std::setprecision(2) << std::fixed;
		std::cout << "The total is: $" << getTotalCost() << std::endl;
		
		// Prompt user to enter amount paid
		std::cout << "Enter the amount paid: $";
		std::cin >> paid;
		std::cin.ignore();
		std::cout << std::endl;

		amountPaid = paid;
	}
}

//************************
//* Function definitions *
//************************

// Get confirmation
std::string ShoppingCart::getConfirmation() {
	std::string input;
	getline(std::cin, input);
	return input;
}

// Add items to cart
void ShoppingCart::addItems(Bundle &b) {			
	int count = 0;			// Number of books in cart
	std::string repeat;		// To loop adding of books

	// Sort bundle by ISBN for searchability
	sortISBN(b);

	std::cout << "Please enter Book ISBNs to add items to the cart.\n";
	do {		
		// Prompt user for ISBN
		int userISBN;
		std::cout << "ISBN: ";
		std::cin >> userISBN;
		std::cin.ignore();
		std::cout << std::endl;

		// Search main bundle for userISBN
		int pos = searchISBN(b, userISBN);

		// If book is found
		if (pos >= 0) {
			// Print book details
			std::cout << "\n---------------------------------------------------------------------------\n\n";
			printBook(b[pos]);
			std::cout << "---------------------------------------------------------------------------\n";

			// Prompt user for confirmation to add to cart
			std::cout << "\nAdd this item to cart? (y/n): ";
			std::string confirm = getConfirmation();
			
			// If add is confirmed
			if (confirm == "y" || confirm == "Y") {
				// If item is in stock
				if (b[pos].getQuantity() > 0) {
					// Add book to cart
					addBook(b[pos]);
					std::cout << "'" << b[pos].getTitle() << "' added to cart.\n\n";

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

// Sort main bundle by isbn
void ShoppingCart::sortISBN(Bundle &b)				
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
			m_books.swap(b[ind], b[swapInd]);
		}
	}
}

// Search main bundle for isbn, returns index position or -1
int ShoppingCart::searchISBN(Bundle &b, int search)		
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

// Calculate all total values
void ShoppingCart::processTotals()		
{
	for (int i = 0; i < getSize(); i++) {
		addSubtotal(m_books[i].getPrice());
		addTotalProfit(m_books[i].getPrice() - m_books[i].getCost());
	}
	calculateTotal();
}

// Validate status of cart
void ShoppingCart::validateCart()		
{
	if (getSize() > 0 && amountPaid >= totalCost) {
		completeCart = true;
	}
	else {
		completeCart = false;
	}
}

// Print book details
void ShoppingCart::printBook(Book book) {
	std::cout << std::setprecision(2) << std::fixed;
	std::cout << book.getTitle() << std::endl;
	std::cout << "by " << std::setw(50) << std::left << book.getAuthor() << "$" << book.getPrice() << std::endl;
	std::cout << std::endl;
}

// Print all books in cart
void ShoppingCart::printAll() {
	for (int i = 0; i < getSize(); i++)
	{
		std::cout << "Item #" << i + 1 << std::endl;
		printBook(m_books[i]);
	}
}