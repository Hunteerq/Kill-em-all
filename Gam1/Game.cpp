#include "stdafx.h"
#include "Game.h"

Game::Game(int wi, int hi, std::string na) : width(wi), height(hi), name(na), Window(sf::VideoMode(wi, hi), na), Player("Artur", 1400, 860, 110.f, 90.f)
{}

Game::~Game()
{ /*my existance is pointless*/ }

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (Window.isOpen())
	{
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
	else if (key == sf::Keyboard::Space)
	{
		allowToShoot = !isPressed;
		if (allowToShoot)
		{
			Player.shoot(); 
		}
	}
	else if (key == sf::Keyboard::Escape)
		Window.close();

}

void Game::update(sf::Time deltaTime)
{
	sf::Vector2f movement(0.f, 0.f);
	sf::Vector2f tempVector = Player.sprite.getPosition();

	if (tempVector.y > Player.getOffSetTop() && isMovingUp) movement.y -= playerSpeed;
	if (tempVector.y < height && isMovingDown) movement.y += playerSpeed;
	if (tempVector.x > 0 && isMovingLeft) movement.x -= playerSpeed;
	if (tempVector.x < width - Player.getOffSetRight() && isMovingRight) movement.x += playerSpeed;
	Player.sprite.move(movement * deltaTime.asSeconds());

	Player.moveBullets();
}

void Game::render()
{
	Window.clear();
	Window.draw(Player.sprite);
	for (int i = 0; i < Player.bullet.size(); i++)
	{
		Window.draw(Player.bullet[i]);
	}
	Window.display();
}
