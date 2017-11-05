#include "stdafx.h"
#include "Hero.h"


Hero::Hero(std::string nam, int wi, int hi, float offSetT, float offSetR) 
	: name(nam), width(wi), height(hi), offSetTop(offSetT), offSetRight(offSetR), sprite(), texture() 
{ }

Hero::~Hero()
{
	//my existence is pointless
}

float Hero::getOffSetRight()
{
	return offSetRight;
}

float Hero::getOffSetTop()
{
	return offSetTop;
}
