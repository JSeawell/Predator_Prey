/*******************************************************************************
** Project: Group Project, Doodlebugs
** Author:
** Date:
** Description: Critter class implementation file
*******************************************************************************/

#include "critter.hpp"

/*******************************************************************************
** Description: Critter default constructor
*******************************************************************************/
Critter::Critter(int age, bool hasMoved, std::string type, char symbol):
	age(age),
	hasMoved(hasMoved),
	type(type),
	symbol(symbol)
{
}

/*******************************************************************************
** Description: Increments age
*******************************************************************************/
void Critter::addDay()
{
	this->age++;
	this->hasMoved = false;
	return;
}

bool Critter::hasEmptySpace(std::vector<Critter**> neighborsVector) const
{
	bool result = false;

	// checks for an empty space among the neighbors
	for (size_t i = 0; i < neighborsVector.size(); i++)
	{
		if (*neighborsVector[i] == nullptr)
		{
			result = true;
		}
	}

	return result;
}
