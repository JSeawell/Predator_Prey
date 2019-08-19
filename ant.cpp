/*******************************************************************************
** Project: Group Project, Doodlebugs
** Author:
** Date:
** Description: Ant class implementation file
*******************************************************************************/

#include "ant.hpp"

int Ant::numberOfAnts = 0;

/*******************************************************************************
** Description: Moves ant to valid, random neighboring cell if possible
*******************************************************************************/
Critter* Ant::move(std::vector<Critter**> &neighborsVector)
{
	int size = neighborsVector.size();
	int index = std::rand() % size;
	Critter *tmp;

	// if an empty space can be found
	if (this->hasEmptySpace(neighborsVector))
	{
		// find an empty space
		while (*neighborsVector[index] != nullptr)
		{
			index = std::rand() % size;
		}
		// move into new space
		*neighborsVector[index] = this;
		// move out of current space
		tmp = nullptr;
	}
	// else cannot move
	else
	{
		// stay in current space
		tmp = this;
	}
	this->hasMoved = true;
	return tmp;
}


/*******************************************************************************
** Description: Adds ant offsprint to valid, random neighboring cell if possible
*******************************************************************************/
void Ant::breed(std::vector<Critter**> &neighborsVector)
{
	int size = neighborsVector.size();
	int index = std::rand() % size;

	// if can breed and an empty space can be found
	if (this->age > 3 && this->hasEmptySpace(neighborsVector))
	{
		// find an empty space
		while (*neighborsVector[index] != nullptr)
		{
			index = std::rand() % size;
		}
		// breed ito empty space
		*neighborsVector[index] = new Ant;
		this->age = 0;
	}
	return;
}
