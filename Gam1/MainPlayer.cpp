#include "stdafx.h"
#include "MainPlayer.h"
#pragma warning (disable: 4996)


MainPlayer::MainPlayer(std::string namee, int widthh, int heightt, float offSetT, float offSetR): Hero(namee, widthh, heightt, offSetT, offSetR), kills(0)
{
	/*  LOADING ALL NEEDED TEXTURES AND FONTS   */
	try { loadFontsForKillsAndText(); }
	catch (std::string e)
	{
		MessageBox(NULL, L"No font in file directory, add AvengenceFont.ttf to media/fonts directory, or download good version from https://github.com/Hunteerq/Kill-em-all", L"Error from loading", MB_ICONERROR | MB_OK);
		std::cout << e << std::endl;	getchar();		exit(4);
	}

	try { setTextureMainHero(); }
	catch (std::string e)
	{
		MessageBox(NULL, L"No hero texture in file directory, add hero.png to media/heroes directory, or download good version from https://github.com/Hunteerq/Kill-em-all", L"Error from loading", MB_ICONERROR | MB_OK);
		std::cout << e << std::endl;      getchar();    exit(4);
	}

	try { setTextureToBullet(); }
	catch (std::string e)
	{
		MessageBox(NULL, L"No bullet texture in file directory, add bullet.png to media/weapons directory, or download good version from https://github.com/Hunteerq/Kill-em-all", L"Error from loading", MB_ICONERROR | MB_OK);
		std::cout << e << std::endl;      getchar();    exit(4);
	}



}

MainPlayer::~MainPlayer()
{ /* My existence is pointless */}

void MainPlayer::setTextureMainHero()
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

void MainPlayer::setTextureToBullet()
{
	if (!bulletTexture.loadFromFile("media/weapons/bullet.png"))
	{
		std::string exception = "Nie ma tekstury bullet.png";
		throw  exception;
	}

}

void MainPlayer::shoot()
{
	sf::Vector2f adjust(35.f, -120.f); //center bullet relatively to Hero
	bullet.push_back(sf::Sprite());
	bullet[bullet.end() - bullet.begin() - 1].setTexture(bulletTexture);
	bullet[bullet.end() - bullet.begin() - 1].setPosition(sprite.getPosition() + adjust);
}

void MainPlayer::moveBullets()
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

void MainPlayer::loadFontsForKillsAndText()
{
	if (!fontForKills.loadFromFile("media/fonts/AvengenceFont.ttf"))
	{
		std::string exceptionFont = "Nie ma fontu w folderze media/fonts";
		throw exceptionFont;
	}

	textForKills[0].setString("Kills");
	textForKills[1].setString(std::to_string(kills));
	for (int i = 0; i < 2; i++) 
	{
		textForKills[i].setFont(fontForKills);
		textForKills[i].setColor(sf::Color::Red);
		textForKills[i].setCharacterSize(30);
		textForKills[i].setPosition(sf::Vector2f(i*15.f, i*30.f));
	}
}