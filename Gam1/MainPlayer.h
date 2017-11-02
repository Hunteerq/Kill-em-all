#pragma once
#include "Hero.h"

class MainPlayer :
	public Hero
{
public:
	std::vector<sf::Sprite> bullet;
	void shoot();
	void moveBullets();
	MainPlayer(std::string namee, int widthh, int heightt, float offSetT, float offSetR);
	~MainPlayer();

private:
	void setTextureMainHero();
	void setTextureToBullet();

	sf::Texture bulletTexture;
	float bulletSpeed = -10.0f;


};

