#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include <Windows.h>


class Hero
{
public:
	Hero(std::string nam, int wi, int hi, float offSetT, float offSetR);
	~Hero();
	sf::Sprite sprite;

	float getOffSetTop();
	float getOffSetRight();



protected:
	sf::Texture texture;
	std::string name;
	int life, width, height;
	float offSetTop, offSetRight;


};

