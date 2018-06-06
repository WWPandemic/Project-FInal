#pragma once
#include <string>
#include "Bundle.h"
#include "Date.h"
#include "ShoppingCart.h"

class CashRegister
{
private:
	Date currentDate;					// Current date
	double balance;						// Total money in cash register
	double totalSales;					// Total sales
	double totalTax;					// Total taxes
	double totalProfit;					// Total profit
	int transactions;					// Number of transactions
	int booksSold;						// Number of books sold

public:
	// Constructors
	CashRegister();
	
	// Accessors 
	std::string getDate();				// Return date as string
	double getBalance() const;			// Return balance
	double getSales() const;			// Return totalSales
	double getProfit() const;			// Return totalProfit
	double getTax() const;				// Return totalTax
	int getTransactions() const;		// Return transactions
	int getBooksSold() const;			// Return booksSold

	// Mutators
	void setDate(int m, int d, int y);	// Set currentDate
	void setBalance(double b);			// Set balance
	void addSales(double s);			// Add amount to totalSales
	void addTax(double t);				// Add amount to totalTax
	void addProfit(double p);			// Add amount to totalProfit
	void addTransaction();				// Add one to transactions
	void addBookSold();					// Add one to booksSold

	// Functions
	ShoppingCart newTransaction(Bundle b);		// Create a new transaction (pass main book bundle)
	void refundBook(Bundle b);					// Refund a book (pass main book bundle)
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