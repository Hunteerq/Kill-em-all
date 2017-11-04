#include "stdafx.h"
#include "Game.h"

Game::Game(int wi, int hi, std::string na) : width(wi), height(hi), name(na), Window(sf::VideoMode(wi, hi), na), Player("Artur", wi, hi, 110.f, 90.f), menu(wi, hi)
{
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
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update(timePerFrame);
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
	Player.moveBullets();
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