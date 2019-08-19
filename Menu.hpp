/*******************************
 *          Menu Class
 *
 *         Header File
 *******************************/
#ifndef Menu_hpp
#define Menu_hpp

#include<string>

class Menu
{
public:
	Menu(int howMany, std::string title);
	~Menu();
	std::string getOption(int number);
	void setOption(int num, std::string option);
	int displayMenu();

private:
	std::string menuTitle;
	int howManyOptions;
	std::string* strArray;
};
#endif
