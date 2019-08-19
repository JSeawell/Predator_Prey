/*******************************
		   Menu Class
*******************************/

#include "Menu.hpp"
#include "intVal.hpp"

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::string;

/******************************
		  Menu::Menu

This is how the menu class
would be implemented in a
function/program:

The menu class is a modular class useful when you want
a menu with 3 or more options. For only 2 options,
the choiceFunction function is a better option.

	Menu menu1(3, "::Menu::");
//This creates a 3 option menu called ::Menu::
//Quit is always the last option
		menu1.setOption(1, "Option1"); // Sets option 1
		menu1.setOption(2, "Option2"); // Sets option 2
	menu1.setOption(3, "Option3"); // Sets option 3
		menu1.displayMenu(); //displays menu and returns choice

	include "intVal" function for bounds check

******************************/
Menu::Menu(int howMany, string title)
{
	menuTitle = title;
	howManyOptions = (howMany + 1);
	strArray = new string[howManyOptions];
}

/*****************************
 * Destructor: deletes menu
 *
 * **************************/
Menu::~Menu()
{
	delete [] strArray;
}

/*****************************
	   Menu::setOption
 ****************************/
void Menu::setOption(int optNum, string option)
{
	strArray[0] = "Quit";
	strArray[optNum] = option;
}

/*****************************
	  Menu::displayMenu
 ****************************/
int Menu::displayMenu()
{
	cout << endl << menuTitle << endl << endl;
	for (int i = 1; i < howManyOptions; i++)
	{
		cout << (i) << ": ";
		cout << strArray[i] << endl;
	}
	cout << "0: Quit" << endl << endl;

	cout << "Please choose an option:" << endl;
	int output = 0;
	int choice;
	choice = minMaxValidation(integerValidation(),0,(howManyOptions - 1));
	for (int i = 0; i < howManyOptions; i++)
	{
		if (choice == (i + 1))
		{
			cout << "You chose: ";
			cout << (strArray[i + 1]) << endl;
			output = (i + 1);
		}
		else if (choice == 0)
		{
			//cout << "Program quit." << endl;
			output = 0;
		}
	}
	return output;
}
