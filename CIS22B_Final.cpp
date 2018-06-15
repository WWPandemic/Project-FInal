#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "Bundle.h"

using namespace std;

int main() {
	Date testDate1(6, 5, 2018);

	Book testBook1("0", "0", "0", 1, testDate1, 2, 1, 1);
	
	Bundle testBundle(25);
	//cout << testBundle[0] << endl;
	testBundle[0] = testBook1;
	//Bundle testBundle2 = testBundle;
	//cout << testBundle2[0] << endl;
	//testBundle.printAll();

	cout << "Please press the <Enter> key to exit" << endl;
	cin.get();
	return 0;
}