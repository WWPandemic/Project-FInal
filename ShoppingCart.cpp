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

ShoppingCart::ShoppingCart(Bundle mainBundle)
{
	subtotal = 0.0;
	totalCost = 0.0;
	totalProfit = 0.0;
	amountPaid = 0.0;
	change = 0.0;

	addItems(mainBundle);
	processTotals();
	processPay();
	calculateChange();
	validateCart();
}

ShoppingCart::~ShoppingCart()
{
	delete [] getBundle();
}

//************************
//* Accessor definitions *
//************************

double ShoppingCart::getSubtotal() const		// Return subtotal
{
	return subtotal;
}

double ShoppingCart::getTotalCost() const		// Return totalCost
{
	return totalCost;
}

double ShoppingCart::getTotalProfit() const		// Return totalProfit
{
	return totalProfit;
}

double ShoppingCart::getAmountPaid() const		// Return amountPaid
{
	return amountPaid;
}

double ShoppingCart::getChange() const		// Return change
{
	return change;
}

double ShoppingCart::getTax() const		// Return tax amount
{
	return subtotal * (TAX_RATE/100);
}

bool ShoppingCart::getComplete() const		// Return complete cart status
{
	return completeCart;
}

//***********************
//* Mutator definitions *
//***********************

void ShoppingCart::addSubtotal(double c)			// Add amount to subtotal
{
	subtotal += c;
}

void ShoppingCart::addTotalProfit(double p)			// Add amount to totalProfit
{
	totalProfit += p;
}

void ShoppingCart::calculateTotal()					// Calculate totalCost
{
	totalCost = subtotal + getTax();
}

void ShoppingCart::calculateChange()				// Calculate change
{
	change = amountPaid - totalCost;
}

void ShoppingCart::processPay()						// Input value for amountPaid
{
	double x;
	std::cout << "\nEnter the amount paid: $";	// Needs validation
	std::cin >> x;
	std::cout << std::endl;
	
	amountPaid = x;
}

//************************
//* Function definitions *
//************************

void ShoppingCart::addItems(Bundle mainBundle) {		// Add items to cart
	std::string repeat = "";
	std::cout << "Please enter Book ISBNs to add items to the cart.\n";
	do {
		int userISBN;
		std::cout << "ISBN: ";
		std::cin >> userISBN;

		// Search mainbundle for userISBN
		int pos = searchISBN(mainBundle, userISBN);
		if (pos >= 0) {
			Book *currentSearch = mainBundle.getBundle();
			if ((currentSearch + pos)->getQuantityOnHand() > 0) {
				addBook(*(currentSearch + pos));
			} else {
				std::cout << "Book out of stock!\n";
			}
		}
		else {
			std::cout << "Could not find specified book!\n\n";
		}

		// Prompt for another search
		std::cout << "Add another item? (y/n): ";
		getline(std::cin, repeat);
	} while (repeat == "y" || repeat == "Y");
}

void ShoppingCart::sortISBN(Bundle b)				// Sort main bundle by isbn
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

int ShoppingCart::searchISBN(Bundle b, int search)		// Search main bundle for isbn, returns index position or -1
{
	Book *bundle = b.getBundle();
	int first = 0;
	int last = b.getSize();
	int mid = 0;
	
	sortISBN(b);

	while (first <= last) {
		mid = (first + last) / 2;
		if ((bundle + mid)->getISBN() == search) {
			return mid;			// If found, return index
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

void ShoppingCart::processTotals()		// Calculate all total values
{
	Book *item = getBundle();
	for (int i = 0; i < getSize(); i++) {
		addSubtotal((item + i)->getRetailPrice());
		addTotalProfit((item + i)->getRetailPrice() - (item + i)->getWholesaleCost());
	}
	calculateTotal();
}

void ShoppingCart::validateCart()		// Validate status of cart
{
	if (getSize() > 0 && amountPaid >= totalCost) {
		completeCart = true;
	}
	else {
		completeCart = false;
	}
}

void ShoppingCart::printAll() {
	Book *b = getBundle();
	for (int i = 0; i < getSize(); i++)
	{
		std::cout << std::setprecision(2) << std::fixed;
		std::cout << "Item #" << i + 1 << ":\n";
		std::cout << (b + i)->getTitle() << std::endl;
		std::cout << "by " << std::setw(40) << std::left << (b + i)->getAuthor() << "$" << (b + i)->getRetailPrice() << std::endl;
		std::cout << std::endl;
	}
}