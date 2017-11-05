#pragma once
#include "Hero.h"
#include <Windows.h>

class MainPlayer :
	public Hero
{
public:
	void shoot();
	void moveBullets();
	MainPlayer(std::string namee, int widthh, int heightt, float offSetT, float offSetR);
	~MainPlayer();

	std::vector<sf::Sprite> bullet;
	sf::Text textForKills[2];
	
	int ballOffsetR, ballOffsetT;
	int kills;

private:
	void setTextureMainHero();
	void setTextureToBullet();
	void loadFontsForKillsAndText();


	sf::Font fontForKills;
	sf::Texture bulletTexture;
	float bulletSpeed = -10.0f;


};

