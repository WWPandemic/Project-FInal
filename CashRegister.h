#pragma once
#include <string>
#include "Bundle.h"
#include "Date.h"
#include "ShoppingCart.h"
#include "Menu.h"

class CashRegister : public Menu
{
private:
	// CashRegister variables
	const double TAX_RATE = 9.0;		// Current city tax rate
	Date currentDate;					// Current date
	double balance;						// Total money in cash register
	double totalSales;					// Total sales
	double totalTax;					// Total taxes
	double totalProfit;					// Total profit
	int transactions;					// Number of transactions
	int booksSold;						// Number of books sold

	// Mutators
	void setDate();						// Set current date
	void setBalance();					// Set balance
	void addBalance(double b);			// Add amount to balance
	void addSales(double s);			// Add amount to totalSales
	void addTax(double t);				// Add amount to totalTax
	void addProfit(double p);			// Add amount to totalProfit
	void addTransaction();				// Add one to transactions
	void addBookSold(int b);			// Add amount to booksSold
	void refundMoney(Book *b);			// Reduce book amounts from register

	// Menu
	void getInput();
	void runOptions();

public:
	// Constructors
	CashRegister(Bundle b);

	// Functions
	std::string getDate();						// Return date as string
	void newTransaction(Bundle b);				// Create a new transaction (pass main book bundle)
	void processCart(ShoppingCart c);			// Adds cart values to register
	void reduceStock(Bundle b, ShoppingCart c);	// Adjust inventory based on purchased items
	void refundBook(Bundle b);					// Refund a book (pass main book bundle)
	int searchISBN(Bundle b, int search);		// Search main bundle for isbn
	void printReceipt(ShoppingCart c);			// Print details of current transaction
	void printSalesReport();					// Print sales report of cash register
	void printLines(int l);						// Print lines for formatting
};



/*
Main functions of register:
1. Process a customer transaction
	- Create a shopping cart for books the customer is buying
	- Adjust cash register values and main bundle inventory
	- Print receipt when done
2. Process a customer refund
	- Adjust cash register values
	- Add book back to main bundle inventory
3. Print a sales report
	- Print all details of register
*/