#pragma once
#include "MainPlayer.h"

class Game
{
public:
	Game(int wi, int hi, std::string na);
	~Game();
	void run();

private:
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	void processEvents();
	void update(sf::Time deltaTime);
	void render();

	MainPlayer Player;

	sf::RenderWindow Window;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);
	std::string name;

	bool isMovingUp = false, isMovingDown = false, isMovingLeft = false, isMovingRight = false, allowToShoot = true;
	float playerSpeed = 660.f;
	int width, height;

};

