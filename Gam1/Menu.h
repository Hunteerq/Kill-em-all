#pragma once
#include <SFML\Graphics.hpp>
#include <Windows.h>



class Menu
{
public:
	void loadFonts();
	void menuSwap(sf::Keyboard::Key key, bool menuPressed);
	bool getUseMenu();
	void setUseMenu(bool temp);
	Menu(int wi, int hi);
	~Menu();

	int menuElements;
	sf::Text *text;
	sf::Text textIfLose[3];


private:
	sf::Font fontOne;
	int width, height, currentIndex;
	bool useMenu;

};

