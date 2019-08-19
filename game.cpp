/*******************************************************************************
** Project: Group Project, Doodlebugs
** Author:
** Date:
** Description: Game class implementation file
*******************************************************************************/

#include "game.hpp"
#include "doodlebug.hpp"
#include "ant.hpp"
#include <iostream>
#include <iomanip>
#include "Menu.hpp"
#include "intVal.hpp"

/*******************************************************************************
** Description: Initializes game, handling user input and memory allocation
*******************************************************************************/
Game::Game()
{
	Menu menu1(2, "::Menu::");
	menu1.setOption(1, "Play Game: (default settings)");
	menu1.setOption(2, "Play Custom Game: (custom settings)");
	int choice = menu1.displayMenu();
	this->prevTimeSteps = 0;
	// if the user does not choose quit
	if (choice != 0)
	{
		std::srand(std::time(NULL));
		int numberOfDoodles;
		int numberOfAnts;
		// if the user chooses default game parameters
		if (choice == 1)
		{
			this->rows = 20;
			this->cols = 20;
			this->steps = 100;
			numberOfDoodles = 5;
			numberOfAnts = 100;
		}
		// else the user chooses custom game parameters
		else if (choice == 2)
		{
			std::cout << std::endl << "This is the extra credit option:" << std::endl << std::endl;
			// get rows
			std::cout << "How many rows?" << std::endl;
			this->rows = minMaxValidation(integerValidation(),2,99);
			// get cols
			std::cout << "How many columns?" << std::endl;
			this->cols = minMaxValidation(integerValidation(),2,99);
			// get number of ants
			int maxAnts = this->rows * this->cols - 1;
			std::cout << "How many ants?" << std::endl;
			numberOfAnts = minMaxValidation(integerValidation(),1,maxAnts);
			// get number of doodles
			int maxDoodles = this->rows * this->cols - numberOfAnts;
			std::cout << "How many Doodlebugs?" << std::endl;
			numberOfDoodles = minMaxValidation(integerValidation(),1,maxDoodles);
		}
		// allocate memory
		this->board = new Critter**[rows];
		for (int i = 0; i < rows; i++)
		{
			this->board[i] = new Critter*[cols];
			for (int j = 0; j < cols; j++)
			{
				this->board[i][j] = nullptr;
			}
		}
		// add doodles to board
		while (Doodlebug::getNumberOfDoodlebugs() < numberOfDoodles)
		{
			this->addDoodlebug();
		}
		// add ants to board
		while (Ant::getNumberOfAnts() < numberOfAnts)
		{
			this->addAnt();
		}
		// while user wants to continue playing
		while (choice !=0)
		{
			// get number of time steps
			std::cout << "How many time steps?" << std::endl;
			this->steps = minMaxValidation(integerValidation(),1,999);
			// run simulation
			this->play();
			// allow user to continue playing
			this->prevTimeSteps += this->steps;
			std::cout << "Enter 1 to continue, 0 to quit: ";
			choice = minMaxValidation(integerValidation(),0,1);
		}
	}
	std::cout << "Program ended." << std::endl;
	return;
}

/*******************************************************************************
** Description: Handles memory deallocation when the game is finished
*******************************************************************************/
Game::~Game()
{
	// for each critter
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			// delete critter
			if (this->board[i][j] != nullptr)
			{
				delete board[i][j];
			}
		}
		// delete rows
		delete [] board[i];
	}
	// delete board
	delete [] board;
	return;
}

/*******************************************************************************
** Description: Primary game loop, iterating once per number of time steps
*******************************************************************************/
void Game::play()
{
	std::cout << "Press enter to continue" << std::endl;
	std::cin.ignore();
	std::cout << "Initial board:" << std::endl;
	// print the step number before the board is displayed each time
	std::cout << std::setw(4) << std::right << "s" + std::to_string(this->prevTimeSteps);
	this->printGame();
	std::cout << "Press enter to proceed to the next time step" << std::endl;
	std::cin.ignore();
	// for each time step
	for (int i = 0; i < this->steps; i++)
	{
		this->moveCritters("Doodlebug");
		this->moveCritters("Ant");
		this->ageCritters();
		this->starveDoodlebugs();
		// print the step number before the board is displayed each time
		std::cout << std::setw(4) << std::right << "s" + std::to_string(i + 1 + this->prevTimeSteps);
		this->printGame();
		std::cout << "Press enter to proceed to the next time step" << std::endl;
		std::cin.ignore(); //pause for user to continue
	}
	return;
}

/*******************************************************************************
** Description: Instructs each critter of type `type` to move
*******************************************************************************/
void Game::moveCritters(std::string type)
{
	// for each critter
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			// if there is a critter of type `type` that hasn't moved yet
			Critter *c = this->board[i][j];
			if (c != nullptr && c->getType() == type && c->getHasMoved() == false)
			{
				std::vector<Critter**> neighborsVector = this->getNeighbors(i, j);
				this->board[i][j] = c->move(neighborsVector);
			}
		}
	}
	return;
}

/*******************************************************************************
** Description: Ages, instructs each critter to breed according to its own logic
*******************************************************************************/
void Game::ageCritters()
{
	// for each critter
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			// if there is a critter in this cell
			Critter *c = this->board[i][j];
			if (c != nullptr)
			{
				std::vector<Critter**> neighborsVector = this->getNeighbors(i, j);
				c->addDay();
				c->breed(neighborsVector);
			}
		}
	}
	return;
}

/*******************************************************************************
** Description: Removes any starved doodlebugs from the board
*******************************************************************************/
void Game::starveDoodlebugs()
{
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			// if there is a doodlebug in this cell
			Doodlebug *d = static_cast<Doodlebug*>(this->board[i][j]);
			if (d != nullptr && d->getType() == "Doodlebug")
			{
				// if it has starved
				if (d->hasStarved())
				{
					delete d;
					this->board[i][j] = nullptr;
				}
			}
		}
	}
	return;
}

/*******************************************************************************
** Description: Prints the board
*******************************************************************************/
void Game::printGame()
{
	// for each column
	std::cout << " ";
	for (int i = 0; i < this->cols; i++)
	{
		// print column headers
		std::cout << std::setw(3) << std::right << std::to_string(i) + " ";
	}
	std::cout << std::endl;
	// for each row
	for (int i = 0; i < this->rows; i++)
	{
		// print row headers
		std::cout << std::setw(4) << std::right << i << " ";
		// for each column
		for (int j = 0; j < this->cols; j++)
		{
			// print critter
			Critter *c = this->board[i][j];
			if (c == nullptr)
			{
				std::cout << std::setw(3) << "__|";
			}
			else
			{
				std::cout << "_" << c->getSymbol() << "|";
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	std::cout << "Number of Doodlebugs: " << Doodlebug::getNumberOfDoodlebugs() << std::endl;;
	std::cout << "Number of Ants: " << Ant::getNumberOfAnts() << std::endl;;
	std::cout << "*****";
	for (int i = 0; i < cols; i++)
	{
		std::cout << "***";
	}
	std::cout << std::endl;
}

/*******************************************************************************
** Description: Returns vector of pointers to the board's pointers representing
**	the critters in the cells surrounding `row`, `col`, handling bounds checking
*******************************************************************************/
std::vector<Critter**> Game::getNeighbors(int row, int col)
{
	std::vector<Critter**> neighborsVector;
	// if there is a row above `row`, add it
	if (row > 0)
	{
		neighborsVector.push_back(&this->board[row - 1][col]);
	}
	// if there is a col to the left of `col`, add it
	if (col > 0)
	{
		neighborsVector.push_back(&this->board[row][col - 1]);
	}
	// if there is a row below `row`, add it
	if (row < (this->rows - 1))
	{
		neighborsVector.push_back(&this->board[row + 1][col]);
	}
	// if there is a col to the right of `col`, add it
	if (col < (this->cols - 1))
	{
		neighborsVector.push_back(&this->board[row][col + 1]);
	}
	return neighborsVector;
}

/*******************************************************************************
** Description: Tries to add a doodlebug to a random cell on the board
*******************************************************************************/
void Game::addDoodlebug()
{
	int row = std::rand() % this->rows;
	int col = std::rand() % this->cols;
	if (this->board[row][col] == nullptr)
	{
		this->board[row][col] = new Doodlebug;
	}
	return;
}

/*******************************************************************************
** Description: Tries to add a ant to a random cell on the board
*******************************************************************************/
void Game::addAnt()
{
	int row = std::rand() % this->rows;
	int col = std::rand() % this->cols;
	if (this->board[row][col] == nullptr)
	{
		this->board[row][col] = new Ant;
	}
	return;
}


