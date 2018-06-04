// ShoppingCart class definitions
#include <iostream>
#include "ShoppingCart.h"

ShoppingCart::ShoppingCart()
{
	double subtotal = 0.0;
	double totalCost = 0.0;
	double totalProfit = 0.0;
	double amountPaid = 0.0;
	double change = 0.0;
	
	// Ask user for isbns to create dynamic array of Books
		// Validate book exists and in stock
	
	processPay();
}

//************************
//* Accessor definitions *
//************************

double ShoppingCart::getSubtotal()					// Return subtotal
{
	return subtotal;
}

double ShoppingCart::getTotalCost()					// Return totalCost
{
	return totalCost;
}

double ShoppingCart::getTotalProfit()				// Return totalProfit
{
	return totalProfit;
}

double ShoppingCart::getAmountPaid()				// Return amountPaid
{
	return amountPaid;
}

double ShoppingCart::getChange()					// Return change
{
	return change;
}

double ShoppingCart::getTax()						// Return tax amount
{
	return subtotal * TAX_RATE;
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
	totalCost = subtotal + (subtotal * TAX_RATE);
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
