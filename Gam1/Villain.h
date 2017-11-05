#pragma once
#include "Hero.h"
#include <ctime>


class Villain :
	public Hero
{
public:
	Villain(std::string nam, int width, int height, float offSetR, float offSetT);
	~Villain();
	//void setVillainTexture(sf::Texture textureVillain);
    void moveVillain();
	void setTextures(); //

private:
	float speed;
	//sf::Texture *VillainTexturee;
	//void loadTexture();
};

