/*******************************************************************************
** Project: Group Project, Doodlebugs
** Author:
** Date:
** Description: Doodle class implementation file
*******************************************************************************/

#include "doodlebug.hpp"
#include "ant.hpp"

int Doodlebug::numberOfDoodlebugs = 0;

/*******************************************************************************
** Description: Returns true if there is an ant to eat in a neighboring cell
*******************************************************************************/
bool Doodlebug::hasNeighboringAnt(std::vector<Critter**> neighborsVector) const
{
	bool result = false;
	for (size_t i = 0; i < neighborsVector.size(); i++)
	{
		if (*neighborsVector[i] != nullptr && (*neighborsVector[i])->getType() == "Ant")
		{
			result = true;
		}
	}
	return result;
}

/*******************************************************************************
** Description: Eats a neighboring ant, or moves doodle to valid, random
**	neighboring cell if possible
*******************************************************************************/
Critter* Doodlebug::move(std::vector<Critter**> &neighborsVector)
{
	int size = neighborsVector.size();
	int index = std::rand() % size;
	Critter *tmp;
	this->lastMeal++;
	// if ant can be found to eat
	if (this->hasNeighboringAnt(neighborsVector))
	{
		// find ant to eat
		while (*neighborsVector[index] == nullptr || (*neighborsVector[index])->getType() != "Ant")
		{
			index = std::rand() % size;
		}
		// eat ant
		feed(*neighborsVector[index]);
		// move out of current space
		tmp = nullptr;
	}
	// else move like an ant
	else
	{
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
	}
	this->hasMoved = true;
	return tmp;
}

/*******************************************************************************
** Descrition: Causes doodlebug to eat neighboring ant
*******************************************************************************/
void Doodlebug::feed(Critter *&neighbor)
{
	delete neighbor;
	neighbor = this;
	this->lastMeal = 0;
	this->hasMoved = true;
}

/*******************************************************************************
** Description: Breeds doodlebug
*******************************************************************************/
void Doodlebug::breed(std::vector<Critter**> &neighborsVector)
{
	int size = neighborsVector.size();
	int index = std::rand() % size;
	if (this->age > 8 && this->hasEmptySpace(neighborsVector))
	{
		while (*neighborsVector[index] != nullptr)
		{
			index = std::rand() % size;
		}
		*neighborsVector[index] = new Doodlebug;
		this->age = 0;
	}
	return;
}
