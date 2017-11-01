#include "stdafx.h"
#include "Hero.h"


Hero::Hero(std::string nam, int wi, int hi) : name(nam), width(wi), height(hi), sprite(), texture()
{
	try { setTextureMainHero(); }
	catch (std::string e)
	{
		MessageBox(NULL,L"No hero texture in file directory, add hero.png to media/heroes directory",L"Error from loading", MB_ICONERROR | MB_OK);
		std::cout << e << std::endl;      getchar();    exit(4);
	}

	try { setTextureToBullet(); }
	catch (std::string e)
	{
		MessageBox(NULL, L"No bullet texture in file directory, add bullet.png to media/weapons directory", L"Error from loading", MB_ICONERROR | MB_OK);
		std::cout << e << std::endl;      getchar();    exit(4);
	}

}

void Hero::setTextureMainHero()
{
	if (!texture.loadFromFile("media/heroes/hero.png"))
	{
		std::string exception = "Nie ma teksturki glownej postaci";
		throw exception;
	}
	sprite.setTexture(texture);
	sprite.scale(0.2f, 0.2f);
	sprite.rotate(-90.f);
	sprite.setPosition(width / 2.f, height *1.f);
}

void Hero::setTextureToBullet()
{
	if (!bulletTexture.loadFromFile("media/weapons/bullet.png"))
	{
		std::string exception = "Nie ma tekstury bullet.png";
		throw  exception;
	}

}

void Hero::shoot()
{
	sf::Vector2f adjust(35.f, -120.f); //center bullet relatively to Hero
	bullet.push_back(sf::Sprite());
	bullet[bullet.end() - bullet.begin() - 1 ].setTexture(bulletTexture);
	bullet[bullet.end() - bullet.begin() - 1 ].setPosition(sprite.getPosition() + adjust);
}

void Hero::moveBullets()
{
	sf::Vector2f moveBullet(0.f, bulletSpeed); // vector to move bullet vertically
	sf::Vector2f tempForBullet; //needed for getting position of each bullet

	for (int i = 0; i < bullet.size(); i++)
	{
		tempForBullet = bullet[i].getPosition();
		bullet[i].move(moveBullet);
		if (tempForBullet.y < 0.f)
		{
			bullet.erase(bullet.begin() + i);
		}
	}
}

Hero::~Hero()
{
}
