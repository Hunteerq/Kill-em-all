#include "stdafx.h"
#include "Menu.h"

#pragma warning (disable: 4996)



Menu::Menu(int wi, int hi): width(wi), height(hi)
{
	useMenu = true;
	menuElements = 3;
	currentIndex = 0;

	text = new sf::Text[menuElements];

	try { loadFonts();   }
	catch (std::string e)
	{
		MessageBox(NULL, L"No font in file directory, add AvengenceFont.ttf to media/fonts directory", L"Error from loading", MB_ICONERROR | MB_OK);
	}


	for (int i = 0; i < 3; i++)
	{
		text[i].setFont(fontOne);
		//text[i].setColor(sf::Color::White);
		text[i].setPosition(sf::Vector2f(wi / 2 - 200, hi / (menuElements + 1)*1.f * (i+1)));
		text[i].setCharacterSize(100);
	}
	text[0].setColor(sf::Color::Red);
	text[0].setString("Play");
	text[1].setString("Options");
	text[2].setString("Exit");
	
}


Menu::~Menu()
{
	delete[] text;
}


void Menu::loadFonts()
{
	if (!(fontOne.loadFromFile("media/fonts/AvengenceFont.ttf")))
	{
		std::string exception = "Nie ma fontu do wczytania";
		throw exception;
	}

}

void Menu::menuSwap(sf::Keyboard::Key key, bool menuPressed)
{
	
	if (!menuPressed)
	{
		if (key == sf::Keyboard::W)
		{
			text[currentIndex].setColor(sf::Color::White);
			currentIndex = (currentIndex + (menuElements-1)) % 3;
			text[currentIndex].setColor(sf::Color::Red);
		}
		else if (key == sf::Keyboard::S)
		{
			text[currentIndex].setColor(sf::Color::White);
			currentIndex = (currentIndex + 1) % 3;
			text[currentIndex].setColor(sf::Color::Red);
		}

		else if (key == sf::Keyboard::Return)
		{
			if (currentIndex == 0)
			{
				useMenu = false;
			}
			if (currentIndex == 2)
			{
				exit(0);
			}
		}


	}
}

bool Menu::getUseMenu()
{
	return useMenu;
}

void Menu::setUseMenu(bool temp)
{
	useMenu = temp;
}