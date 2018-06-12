#define _CRT_SECURE_NO_WARNINGS
#include "BookReader.h"
#include "MainMenu.h"

using namespace std;

int main()
{
	BookReader reader;
	Bundle b = reader.createBundle();
	//implement reading bundle from samplebooks.txt
	MainMenu mainmenu(b);
	mainmenu.runMenu();

	reader.exportBundle(b);

	cout << "Please press  the <Enter> key to exit" << endl;
	cin.get();
	return 0;
}
