#pragma once
#include "Buffer.h"
#include "Car.h"
#include "Image.h"
#include "Label.h"
#include "CarEnemy.h"
#include <vector>
using namespace std;

class Map
{
private:
	Car car;
	Image scoreBoard;
	Image gameField;
	Label scoreStr;
	Buffer map;
	size_t stepCounter;
	vector<CarEnemy> enemy;
	bool gameOver = false;

public:
	Map(Image scoreBoard, Image gameField, Label scoreStr, Image carTexture);

	Image& GetGameField();
	Image& GetScoreBoard();
	Label& GetScoreStr();
	Buffer& GetBuffer();
	Car& GetCar();

	void Control(int key);

	CarEnemy GetEnemy();
	bool GetGameOver() const;

	void ShowGameOverScreen(Buffer& buffer);
	void LoadToBuffer(Buffer& buffer, __COORD coord);
};

