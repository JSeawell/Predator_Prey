/*******************************************************************************
** Project: Group Project, Doodlebugs
** Author:
** Date:
** Description: Doodlebug class declaration file
*******************************************************************************/

#ifndef _DOODLEBUG_HPP
#define _DOODLEBUG_HPP

#include "critter.hpp"

class Doodlebug : public Critter
{
public:
	Doodlebug():Critter(0, false, "Doodlebug", 'x') {numberOfDoodlebugs++;}
	static int getNumberOfDoodlebugs() {return Doodlebug::numberOfDoodlebugs;}
	virtual ~Doodlebug() {numberOfDoodlebugs--;}
	virtual Critter* move(std::vector<Critter**> &neighborsVector) override;
	virtual void breed(std::vector<Critter**> &neighborsVector) override;
	bool hasStarved() const {return this->lastMeal > 3;}

private:
	static int numberOfDoodlebugs;
	int lastMeal;
	void feed(Critter *&neighbor);
	bool hasNeighboringAnt(std::vector<Critter**> neighborsVector) const;
};

#endif
