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

public:
	// Constructors
	ShoppingCart();

	// Accessors
	double getSubtotal() const;				// Return subtotal
	double getTotalCost() const;			// Return totalCost
	double getTotalProfit() const;			// Return totalProfit
	double getAmountPaid() const;			// Return amountPaid
	double getChange() const;				// Return change
	double getTax() const;					// Return tax amount

	// Mutators
	void addSubtotal(double c);			// Add amount to subtotal
	void addTotalProfit(double p);		// Add amount to totalProfit
	void calculateTotal();				// Calculate totalCost
	void calculateChange();				// Calculate change
	void processPay();					// Input value for amountPaid

};