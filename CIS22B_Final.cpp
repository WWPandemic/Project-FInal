#define _CRT_SECURE_NO_WARNINGS
#include "MainMenu.h"
#include "BookReader.h"

int main()
{
	BookReader br;
	Bundle books = br.createBundle();

	MainMenu mainmenu = MainMenu(books);
	mainmenu.runMenu();

	br.exportBundle(books);

	std::cout << "Please press the <Enter> key to exit" << std::endl;
	std::cin.get();
	return 0;
}