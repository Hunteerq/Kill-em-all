#include "stdafx.h"
#include "Villain.h"


Villain::Villain(std::string nam, int width, int height, float offSetR, float offSetT) : Hero(nam, width, height, offSetR, offSetT)
{
	speed = 0.5f;
	setTextures();
}



Villain::~Villain()
{
}
/*
void Villain::setVillainTexture(sf::Texture textureVillain)
{
	VillainTexturee = new sf::Texture;
	*VillainTexturee = textureVillain;
	sprite.setTexture(*VillainTexturee);
	sprite.scale(0.2f, 0.2f);

}*/


void Villain::moveVillain()
{
	sprite.move(0.f,speed);

}

void Villain::setTextures()
{
	if (!texture.loadFromFile("media/villains/Enemy1.png"))
	{
		exit(4);
	}
	sprite.setTexture(texture);
	sprite.scale(0.2f, 0.2f);
	std::srand(std::time(0));
	int random_width = (std::rand() * 93) % (width - 100);
	sprite.setPosition(sf::Vector2f(random_width * 1.0f, 10.f));

}