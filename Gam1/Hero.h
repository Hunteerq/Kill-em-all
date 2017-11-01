#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include <Windows.h>

class Hero
{
public:
	Hero(std::string nam, int wi, int hi);
	~Hero();
	sf::Sprite sprite;
	std::vector<sf::Sprite> bullet;
	void shoot();
	void moveBullets();


private:
	void setTextureMainHero();
	void setTextureToBullet();
	sf::Texture texture;
	sf::Texture bulletTexture;
	std::string name;
	int life, width, height;
	float bulletSpeed = - 8.0f;
	
};

