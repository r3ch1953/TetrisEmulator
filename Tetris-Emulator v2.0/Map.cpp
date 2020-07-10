#include "Map.h"
#include <ctime>
#include <iostream>
#include <Windows.h>
using namespace std;

Map::Map(Image scoreBoard, Image gameField, Label scoreStr, Image carTexture)
{
	this->car.GetBuffer().Resize(carTexture.GetResolution());
	this->car.GetTexture() = carTexture;

	this->scoreBoard = scoreBoard;
	this->gameField = gameField;
	this->scoreStr = scoreStr;

	this->map.Resize(Resolution{ this->gameField.GetResolution().height + this->scoreBoard.GetResolution().height, this->gameField.GetResolution().width });
}

Image& Map::GetGameField()
{
	return this->gameField;
}

Image& Map::GetScoreBoard()
{
	return this->scoreBoard;
}

Label& Map::GetScoreStr()
{
	return this->scoreStr;
}

Buffer& Map::GetBuffer()
{
	return this->map;
}

Car& Map::GetCar()
{
	return this->car;
}

void Map::Control(int key)
{
	this->car.Control(key, this->map);
}

CarEnemy Map::GetEnemy()
{
	srand(unsigned(time(nullptr)));
	CarEnemy temp(Image::GetFrameFromFile("R_cars.txt", Image::FindResolution("R_cars.txt"), 1));
	temp.GetTexture().SetColor(Color::RED);
	temp.SetSide(Side(rand() % 2));
	temp.LoadTextureToCar();
	return temp;
}

bool Map::GetGameOver() const
{
	return this->gameOver;
}

void Map::ShowGameOverScreen(Buffer& buffer)
{
	this->gameField.SetColor(Color::BRIGHTWHITE);
	this->gameField.LoadToBuffer(buffer, __COORD{0, 0});

	Image temp = Image::GetFrameFromFile("R_end.txt", Image::FindResolution("R_end.txt"), 1);
	temp.SetColor(Color::RED);
	temp.LoadToBuffer(buffer,
		__COORD{ 1, (this->gameField.GetResolution().width / 2) - (Image::FindResolution("R_end.txt").width / 2) });

	this->scoreStr.LoadToBuffer(buffer, __COORD{ 6, (this->gameField.GetResolution().width / 2) - (this->scoreStr.GetLenght() / 2) });
}

void Map::LoadToBuffer(Buffer& buffer, __COORD coord)
{
	this->map.Clear();

	this->car.GetTexture().SetColor(Color::LIGHTBLUE);
	this->scoreStr.Clear();
	this->scoreStr.SetText(("Score: " + to_string(this->car.GetScore())));
	this->scoreStr.SetColor(Color::GREEN);
	this->scoreStr.LoadToBuffer(this->scoreBoard.GetBuffer(), __COORD{ this->scoreBoard.GetResolution().height / 2, 2 });
	this->gameField.SetColor(Color::BRIGHTWHITE);
	this->gameField.LoadToBuffer(this->map, __COORD{0, 0});
	this->scoreBoard.LoadToBuffer(this->map, __COORD{this->gameField.GetResolution().height, 0});
	this->car.LoadToBuffer(this->map);

	if (stepCounter == 0)
		this->enemy.push_back(GetEnemy());

	if (this->enemy[0].GetPop() == true)
		this->enemy.erase(this->enemy.begin());

	for (size_t i = 0; i < this->enemy.size(); i++)
		this->enemy[i].LoadToBuffer(this->map);

	if ((coord.y + this->map.GetHeight()) > buffer.GetHeight() || (coord.x + this->map.GetWidth()) > buffer.GetWidth())
	{
		cout << "Wrong X or Y! Error!\n";
		return;
	}

	for (size_t i = coord.y, mapI = 0; mapI < this->map.GetHeight(); i++, mapI++)
	{
		for (size_t j = coord.x, mapJ = 0; mapJ < (this->map.GetWidth() - this->car.GetTexture().GetResolution().width); j++, mapJ++)
		{
			buffer.Replace(this->map.GetPixel(__COORD{ mapI, mapJ }), __COORD{ i,j });
		}
	}

	for (auto item : this->enemy)
	{
		if (item.CheckCollison(this->map, this->car))
		{
			this->gameOver = true;
			Sleep(500);
			return;
		}
	}

	if (stepCounter % 10 == 0)
		this->car.SetScore(this->car.GetScore() + 1);

	stepCounter++;
	if (stepCounter > 30)
		stepCounter = 0;

	Sleep(1);
}
