#pragma once
#include "Buffer.h"
#include "Image.h"
#include "Figure.h"

class GameField
{
private:
	Buffer field;
	Buffer fallenFigures;
	Image texture;
	Figure figure;
	size_t scores;

public:
	GameField(Image texture);

	void GetNewFigure();

	void Move(int key);
	void Fall();
	bool CheckLines();
	bool CheckParts(vector<__COORD> parts, __COORD coord);

	void LoadFallenFiguresToField();
	void LoadToBuffer(Buffer& buffer, __COORD coord);
};
