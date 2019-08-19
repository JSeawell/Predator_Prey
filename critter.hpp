/*******************************************************************************
** Project: Group Project, Doodlebugs
** Author:
** Date:
** Description: Critter class declaration file
*******************************************************************************/

#ifndef _CRITTER_HPP
#define _CRITTER_HPP

#include <vector>
#include <string>

class Critter
{
public:
	Critter(int age = 0, bool hasMoved = false, std::string type = "", char symbol = ' ');
	virtual ~Critter() {}

	virtual Critter* move(std::vector<Critter**> &neighborsVector) = 0;
	virtual void breed(std::vector<Critter**> &neighborsVector) = 0;
	void addDay();
	std::string getType() {return this->type;}
	bool hasEmptySpace(std::vector<Critter**> neighborsVector) const;
	char getSymbol() const {return this->symbol;}
	bool getHasMoved() const {return this->hasMoved;}

protected:
	int age;
	bool hasMoved;
	std::string type;
	char symbol;
};

#endif
