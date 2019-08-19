/*******************************************************************************
** Project: Group Project, Doodlebugs
** Author:
** Date:
** Description: Game class declaration file
*******************************************************************************/
#ifndef _GAME_HPP
#define _GAME_HPP

#include "critter.hpp"
#include <string>
#include <vector>

class Game
{
public:
	Game();
	~Game();
	void play();

private:
	void addDoodlebug();
	void addAnt();
	void moveCritters(std::string type);
	void ageCritters();
	void starveDoodlebugs();
	void printGame();
	std::vector<Critter**> getNeighbors(int row, int col);
	Critter ***board;
	int rows;
	int cols;
	int steps;
	int prevTimeSteps;
};

#endif
