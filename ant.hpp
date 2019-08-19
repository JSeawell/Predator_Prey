/*******************************************************************************
** Project: Group Project, Doodlebugs
** Author:
** Date:
** Description: Ant class declaration file
*******************************************************************************/

#ifndef _ANT_HPP
#define _ANT_HPP

#include "critter.hpp"

class Ant : public Critter
{
public:
	Ant():Critter(0, false, "Ant", 'o') {numberOfAnts++;}
	static int getNumberOfAnts() {return Ant::numberOfAnts;}
	virtual ~Ant() {numberOfAnts--;}
	virtual Critter* move(std::vector<Critter**> &neighborsVector) override;
	virtual void breed(std::vector<Critter**> &neighborsVector) override;
private:
	static int numberOfAnts;
};

#endif
