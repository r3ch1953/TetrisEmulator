#include "GameField.h"
#include <ctime>
#include <iostream>
#include <functional>
using namespace std;

GameField::GameField(Image texture)
{
	this->texture = texture;
	field.Resize(texture.GetResolution());
	fallenFigures.Resize(texture.GetResolution());
	this->texture.LoadToBuffer(fallenFigures, __COORD{ 0,0 });
	GetNewFigure();
}

void GameField::GetNewFigure()
{
	srand(unsigned(time(nullptr)));
	Color color = Color(rand() % 15 + 1);

	Figure newFigure("T_texture.txt", FigureIndex(rand() % 7 + 1));
	newFigure.GetTexture().SetColor(color);
	//newFigure.GetTexture().SetBackground(color);
	this->figure = newFigure;
}

void GameField::Move(int key)
{
	bool good = true;
	switch (key)
	{
	case 'd':
	case 'D':
		for (auto item : this->figure.GetParts())
		{
			if (this->fallenFigures.GetPixel(__COORD{ (item.y), item.x + 1 }).symbol == '#')
			{
				if (!CheckParts(this->figure.GetParts(), __COORD{ (item.y), item.x + 1 }))
					return;
			}
		}

		for (auto item : this->figure.GetParts())
		{
			if (CheckParts(this->figure.GetParts(), __COORD{ item.y,this->fallenFigures.GetWidth() - 3 }))
				good = false;
			if (!good)
				break;
		}
		if (good)
			this->figure.SetCoord(__COORD{ this->figure.GetCoord().y, this->figure.GetCoord().x + 1 });

		break;

	case 'a':
	case 'A':
		for (auto item : this->figure.GetParts())
		{
			if (this->fallenFigures.GetPixel(__COORD{ (item.y), item.x - 1 }).symbol == '#')
			{
				if (!CheckParts(this->figure.GetParts(), __COORD{ (item.y), item.x - 1 }))
					return;
			}
		}

		if (this->figure.GetCoord().x > 1)
			this->figure.SetCoord(__COORD{ this->figure.GetCoord().y, this->figure.GetCoord().x - 1 });
		break;

	case 32:
		this->figure.Rotate();
		break;
	}
}

void GameField::Fall()
{
	for (auto item : this->figure.GetParts())
	{
		if ((item.y + 1) != this->fallenFigures.GetHeight() - 1)
		{
			if (this->fallenFigures.GetPixel(__COORD{ (item.y + 1), item.x }).symbol == '#')
			{
				if (!CheckParts(this->figure.GetParts(), __COORD{ (item.y + 1), item.x }))
				{
					this->figure.LoadToBuffer(this->fallenFigures);
					GetNewFigure();
					return;
				}
			}
		}
		else if ((item.y + 1) == this->fallenFigures.GetHeight() - 1)
		{
			this->figure.LoadToBuffer(this->fallenFigures);
			GetNewFigure();
			return;
		}
	}
	this->figure.SetCoord(__COORD{ (this->figure.GetCoord().y + 1), this->figure.GetCoord().x });
}

bool GameField::CheckLines()
{
	bool lineIsFound = false;

	__COORD lineStart{ 0,0 };
	__COORD lineEnd{ 0,0 };

	for (size_t i = 1; i < this->fallenFigures.GetHeight(); i++)
	{
		bool good = true;
		for (size_t j = 1; j < this->fallenFigures.GetWidth() - 2; j++)
		{
			if (this->fallenFigures.GetPixel(__COORD{ i,j }).symbol != '#')
			{
				good = false;
				break;
			}
		}

		if (good)
			lineIsFound = true;

		if (lineIsFound)
		{
			lineStart.x = 1;
			lineStart.y = i;
			lineEnd.x = this->fallenFigures.GetWidth() - 2;
			lineEnd.y = i;
			break;
		}
	}

	if (!lineIsFound)
		return lineIsFound;

	for (size_t i = lineStart.y; i < lineEnd.y + 1; i++)
	{
		for (size_t j = lineStart.x; j < lineEnd.x; j++)
		{
			this->fallenFigures.Replace(Pixel{ ' ' }, __COORD{ i, j });
		}
	}

	for (size_t i = this->fallenFigures.GetHeight(); i > 0; i--)
	{
		for (size_t j = this->fallenFigures.GetWidth() - 2; j > 0; j--)
		{

		}
	}

	return lineIsFound;
}

bool GameField::CheckParts(vector<__COORD> parts, __COORD coord)
{
	for (auto item : parts)
	{
		if (item.x == coord.x &&
			item.y == coord.y)
		{
			return true;
		}
	}
	return false;
}

void GameField::LoadFallenFiguresToField()
{
	for (size_t i = 0, figuresI = 0; figuresI < this->fallenFigures.GetHeight(); i++, figuresI++)
	{
		for (size_t j = 0, figuresJ = 0; figuresJ < this->fallenFigures.GetWidth(); j++, figuresJ++)
		{
			this->field.Replace(this->fallenFigures.GetPixel(__COORD{ figuresI, figuresJ }), __COORD{ i,j });
		}
	}
}

void GameField::LoadToBuffer(Buffer& buffer, __COORD coord)
{
	this->texture.LoadToBuffer(this->field, __COORD{0, 0});
	LoadFallenFiguresToField();
	this->figure.LoadToBuffer(this->field);

	if ((coord.y + this->field.GetHeight()) > buffer.GetHeight() || (coord.x + this->field.GetWidth()) > buffer.GetWidth())
	{
		cout << "Wrong X or Y! Error!\n";
		return;
	}

	for (size_t i = coord.y, menuI = 0; i < this->field.GetHeight(); i++, menuI++)
	{
		for (size_t j = coord.x, menuJ = 0; j < this->field.GetWidth(); j++, menuJ++)
		{
			buffer.Replace(this->field.GetPixel(__COORD{ menuI, menuJ }), __COORD{ i,j });
		}
	}
}