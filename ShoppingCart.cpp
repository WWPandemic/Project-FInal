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

ShoppingCart::ShoppingCart(Bundle b)
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
	double paid;
	std::cout << std::setprecision(2) << std::fixed;
	std::cout << "The total is: $" << getTotalCost() << std::endl;
	std::cout << "Enter the amount paid: $";	// Needs validation
	std::cin >> paid;
	std::cin.ignore();
	std::cout << std::endl;
	
	amountPaid = paid;
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
void ShoppingCart::addItems(Bundle b) {			
	int count = 0;
	std::string repeat;

	std::cout << "Please enter Book ISBNs to add items to the cart.\n";
	do {
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
			printBook(b[pos]);

			// Ask to add to cart
			std::cout << "\nAdd this item to cart? (y/n): ";
			std::string confirm = getConfirmation();
			std::cout << std::endl;
			
			if (confirm == "y" || confirm == "Y") {
				// Check if item is in stock
				if (b[pos].getQuantity() > 0) {
					// Add book to cart
					getArray()[count++] = b[pos];
					std::cout << "'" << b[pos].getTitle() << "' added to cart.\n\n";

					// Check cart size
					if (count >= getLength()) {
						getArray().reSize(count + 1);
					}
				}
				else {
					std::cout << "Book is out of stock!\n\n";
				}
			}
		}
		else {
			std::cout << "\nCould not find specified book!\n\n";
		}

		// Prompt for another search
		std::cout << "\nAdd another item? (y/n): ";
		repeat = getConfirmation();
		std::cout << std::endl;
	} while (repeat == "y" || repeat == "Y");
}

// Sort main bundle by isbn
Bundle ShoppingCart::sortISBN(Bundle b)				
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
int ShoppingCart::searchISBN(Bundle b, int search)		
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

// Calculate all total values
void ShoppingCart::processTotals()		
{
	Array<Book> bp = getArray();
	
	for (int i = 0; i < getLength(); i++) {
		addSubtotal(bp[i].getPrice());
		addTotalProfit(bp[i].getPrice() - bp[i].getCost());
	}
	calculateTotal();
}

// Validate status of cart
void ShoppingCart::validateCart()		
{
	if (getLength() > 0 && amountPaid >= totalCost) {
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
	std::cout << "by " << std::setw(40) << std::left << book.getAuthor() << "$" << book.getPrice() << std::endl;
	std::cout << std::endl;
}

// Print all books in cart
void ShoppingCart::printAll() {
	Array<Book> bp = getArray();
	
	for (int i = 0; i < getLength(); i++)
	{
		std::cout << "Item #" << i + 1 << std::endl;
		printBook(bp[i]);
	}
}