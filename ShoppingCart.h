#pragma once
#include "Bundle.h"

class ShoppingCart : public Bundle
{
private:
	const double TAX_RATE = 9.0;	// Current city tax rate
	double subtotal;				// Total cost before taxes
	double totalCost;				// Total cost of ShoppingCart
	double totalProfit;				// Total profit of ShoppingCart
	double amountPaid;				// Total paid by customer
	double change;					// Change owed to customer
	bool completeCart;				// If cart is valid or not

public:
	// Constructors
	ShoppingCart();
	ShoppingCart(Bundle b);

	// Accessors
	double getSubtotal() const;				// Return subtotal
	double getTotalCost() const;			// Return totalCost
	double getTotalProfit() const;			// Return totalProfit
	double getAmountPaid() const;			// Return amountPaid
	double getChange() const;				// Return change
	bool getComplete() const;				// Return complete cart status
	double getTax() const;					// Return tax amount
	
	// Mutators
	void addSubtotal(double);			// Add amount to subtotal
	void addTotalProfit(double);		// Add amount to totalProfit
	void calculateTotal();				// Calculate totalCost
	void calculateChange();				// Calculate change
	void processPay();					// Input value for amountPaid

	// Functions
	std::string getConfirmation();		// Get confirmation
	void addItems(Bundle);				// Add items to cart
	Bundle sortISBN(Bundle);			// Sort bundle by isbn
	int searchISBN(Bundle, int);		// Search main bundle for isbn
	void processTotals();				// Calculate all total values
	void validateCart();				// Validate status of cart
	void printBook(Book);				// Print book details
	void printAll();					// Print all books in cart
};