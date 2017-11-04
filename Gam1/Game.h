#pragma once
#include "MainPlayer.h"
#include "Menu.h"

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
	void showMenu();
	void eventsMenu();
	void loadBackground();

	Menu menu;
	MainPlayer Player;

	sf::Texture backgroundTexture;
	sf::Sprite background;
	sf::RenderWindow Window;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);
	std::string name;

	bool isMovingUp = false, isMovingDown = false, isMovingLeft = false, isMovingRight = false, allowToShoot = true;
	float playerSpeed = 560.f;
	int width, height;

};

