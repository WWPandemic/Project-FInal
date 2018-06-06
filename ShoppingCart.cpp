#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "ShoppingCart.h"

//**************************
//* Constructor definition *
//**************************

ShoppingCart::ShoppingCart()
{
	double subtotal = 0.0;
	double totalCost = 0.0;
	double totalProfit = 0.0;
	double amountPaid = 0.0;
	double change = 0.0;
	
	// Ask user for isbns to create dynamic array of Books
		// Validate book exists and in stock
		// Adjust variables
	
	processPay();
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

/*
To do:
- input validation
- stock validation
- cancel creation of shopping cart
- bundle integration
*/