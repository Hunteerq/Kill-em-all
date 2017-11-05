#include "stdafx.h"
#include "Game.h"

Game::Game(int wi, int hi, std::string na) : width(wi), height(hi), name(na), Window(sf::VideoMode(wi, hi), na), Player("Artur", wi, hi, 110.f, 90.f), menu(wi, hi)
{
	/*try { loadVillain();  }
	catch (std::string e)
	{
		MessageBox(NULL, L"No villain texture in file directory, add Enemy1.png to media/villains directory, or download good version from https://github.com/Hunteerq/Kill-em-all", L"Error from loading", MB_ICONERROR | MB_OK);
		std::cout << e << std::endl; exit(4);
	}*/

	try {	loadBackground(); }
	catch (std::string e)
	{
		MessageBox(NULL, L"No background texture in file directory, add bgDark.png to media/backgrounds directory, or download good version from https://github.com/Hunteerq/Kill-em-all", L"Error from loading", MB_ICONERROR | MB_OK);
		std::cout << e << std::endl; exit(4);
	}
	
	background.setTexture(backgroundTexture);
	background.setPosition(sf::Vector2f(-400.f, 0.f));
}

Game::~Game()
{ /*my existance is pointless*/ }

void Game::run()
{
	int count;
	int iTime = 0;
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	
	while (Window.isOpen())
	{
		while (menu.getUseMenu())
		{
			showMenu();
			clock.restart();
		}
		
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			iTime++;
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update(timePerFrame);
			
			if (iTime > 180)
			{
				iTime = 0;
				villains.push_back(new Villain("Artur", width, height, 73, 72));
			}
		}
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (Window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				Window.close();
				break;
			case sf::Event::KeyPressed:
				handlePlayerInput(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				handlePlayerInput(event.key.code, false);
				break;
		}

	}
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W)
		isMovingUp = isPressed;
	else if (key == sf::Keyboard::S)
		isMovingDown = isPressed;
	else if (key == sf::Keyboard::A)
		isMovingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		isMovingRight = isPressed;
	else if (key == sf::Keyboard::Escape)
		menu.setUseMenu(true);					//TODO: Menu after esc 
	else if (key == sf::Keyboard::Space)
	{
		allowToShoot = !isPressed;
		if (allowToShoot)	Player.shoot();
	}

}

void Game::update(sf::Time deltaTime)
{
	sf::Vector2f movement(0.f, 0.f);
	sf::Vector2f tempVector = Player.sprite.getPosition();		//for tests that Hero won't leave the window after the move

	if (tempVector.y > Player.getOffSetTop() && isMovingUp) movement.y -= playerSpeed;
	if (tempVector.y < height && isMovingDown) movement.y += playerSpeed;
	if (tempVector.x > 0 && isMovingLeft) movement.x -= playerSpeed;
	if (tempVector.x < width - Player.getOffSetRight() && isMovingRight) movement.x += playerSpeed;

	Player.sprite.move(movement * deltaTime.asSeconds());	   // deltaTime should be ~ 1/60
	ifVillainKilled();		// IT FUCKING WORKS <3
	for (int j = 0; j < villains.size(); j++)
		villains[j]->moveVillain();

	Player.moveBullets();
	ifVillainWon();

}

void Game::render()
{
	Window.clear();
	Window.draw(background);
	Window.draw(Player.sprite);
	for (int i = 0; i < Player.bullet.size(); i++)
		Window.draw(Player.bullet[i]);
	for (int i = 0; i < 2; i++)
		Window.draw(Player.textForKills[i]);
	for (int i = 0; i < villains.size(); i++)
		Window.draw(villains[i]->sprite);

	Window.display();
}

void Game::showMenu()
{
	Window.clear();

	eventsMenu();
	for (int i = 0; i < menu.menuElements; i++)
	{
		Window.draw(menu.text[i]);
	}
	Window.display();
}

void Game::eventsMenu()
{
	sf::Event eventMenu;
	while (Window.pollEvent(eventMenu))
	{
		switch (eventMenu.type)
		{
		case sf::Event::Closed:
			Window.close();
			break;
		case sf::Event::KeyPressed:
			menu.menuSwap(eventMenu.key.code, true);
			break;
		case sf::Event::KeyReleased:
			menu.menuSwap(eventMenu.key.code, false);
			break;

		}
	}

}

void Game::loadBackground()
{
	if (!backgroundTexture.loadFromFile("media/backgrounds/bgDark.png"))
	{
		std::string exception = "No background in file directory";
		throw exception;
	}
}

void Game::ifVillainKilled()
{
	sf::Vector2f tempVillain;
	sf::Vector2f tempBullet;


	for (int i = 0; i < villains.size(); i++)
	{
		tempVillain = villains[i]->sprite.getPosition();
		for (int j = 0; j < Player.bullet.size(); j++)
		{
			tempBullet = Player.bullet[j].getPosition();
			if (tempBullet.x >= tempVillain.x - Player.ballOffsetR + 10 && tempBullet.x <= tempVillain.x + 73 + Player.ballOffsetR - 40 && tempBullet.y <= tempVillain.y + 72) //Hit condition
			{
				villains.erase(villains.begin() + i);
				Player.kills++;
				Player.textForKills[1].setString(std::to_string(Player.kills));
			}
		}
	}

}

void Game::ifVillainWon()
{
	for (int i = 0; i < villains.size(); i++)
	{
		if (villains[i]->ifHitTheGround())
		{
			menu.textIfLose[2].setString(Player.textForKills[1].getString());
			Window.clear();
			Window.draw(menu.textIfLose[0]);
			Window.draw(menu.textIfLose[1]);
			Window.draw(menu.textIfLose[2]);
			Window.display();
			sf::Clock clockMenu;
			sf::Time time4sec = sf::Time::Zero;
			while (time4sec.asSeconds() < 4)
			{
				time4sec += clockMenu.restart();
			}
			Player.kills = 0;
			Player.sprite.setPosition(width / 2.0f, height*1.0f);
			for (int j = 0; j < villains.size(); j++)
			{
				villains.erase(villains.begin()+ j );
			}
			for (int k = 0; k < Player.bullet.size(); k++)
			{
				Player.bullet.erase(Player.bullet.begin() + k);
			}
			menu.setUseMenu(true);

		}
	}
}