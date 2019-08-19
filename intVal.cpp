/*****************************************
 *
 *          intVal source file
 *
 * Name: Jake Seawell
 * Date: 09/23/18
 * Description: This is 2 functions for
 * validating integer input by the user
 * and returning that value.
 *
 * **************************************/
#include "intVal.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <cstdlib>
#include <time.h>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::istringstream;
using std::getline;

/* This is how you would use both together in another program:

	 Instead of:
	 cin >> variable;

	 You would use:

	 int variable =  minMaxValidation(integerValidation(), min, max);

*/
/***********************************************
 *             integerValidation
 *
 *  Validates that the input is only an integer.
 *  This function is used by minMaxValidation.
 **********************************************/

int integerValidation()
{
	string input = "";
	//cin >> input; //User enters int in form of string
	while (input.length() == 0)
	{
		cout << "Enter an integer: " << endl;
		std::getline(cin, input);
	}
	int onlyInt = 0;
	while (onlyInt == 0)
	{
		//int i = 0;
		for (size_t i = 0; i < input.length(); i++)
		{
			//check if every "digit" of string is
			//or first "digit" can be '-' for negative #s
			if ((isdigit(input.at(i))) || ((input.at(0) == '-') && (i == 0)))
			{
				onlyInt = 1;
			}
			else if ((!isdigit(input.at(i))) || (input.at(i) == '.'))
			{
				cout << "Invalid Entry. Please enter an integer: " << endl;
				//cin >> input;
				std::getline(cin, input);

				onlyInt = 0;
				break;
			}
		}
	}

	int newInput;
	istringstream(input) >> newInput;//Convert string to integer
	//cout << "You entered: " << newInput << endl;//Display integer
	return newInput;//return integer
}

/***************************************
 *      minMaxValidation
 *
 * Validates whether the integer
 * is within a certain range (min, max).
 * This function uses the
 * integerValidation function (above).
 **************************************/

int minMaxValidation(int input, int min, int max)
{
	// Default Min and Max can be changed as neccessary

	while ((input < min) || (input > max))//This will loop until int is between min and max
	{
		cout << "Invalid entry. Please enter an integer from "
			<< min << " to " << max << "." << endl;

		input = integerValidation();
	}

	return input;//integer is also returned to function
}


/***************************************
 *      minMaxRand()
 *
 * Generates a random integer between
 * two given values
 **************************************/

int minMaxRand(int min, int max)
{
	// Default Min and Max can be changed as neccessary
	// srand(time(0)); // this line is needed once,
	// and only once, in any program using this function

	int input = min + (rand() % (max - min + 1));
	return input;//integer is also returned to function
}

/***************************************
 *      minMaxRandDouble()
 *
 * Generates a random double between
 * two given values
 **************************************/

double minMaxRandDouble(int min, int max)

{
	double output = ((min + (rand() % (max - min))) + ((rand() % 10) / 10.0) + ((rand() % 2) / 10.0));
	return output; //double is also returned to function
}

