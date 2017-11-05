#pragma once
#include "Hero.h"
#include <ctime>


class Villain :
	public Hero
{
public:
	Villain(std::string nam, int width, int height, float offSetR, float offSetT);
	~Villain();
    void moveVillain();
	void setTextures(); 
	bool ifHitTheGround();

private:
	float speed;
	//sf::Texture *VillainTexturee;
	//void loadTexture();
};

