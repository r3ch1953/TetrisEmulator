#pragma once
#include "Buffer.h"
#include "Image.h"
#include <vector>
using namespace std;

enum FigureIndex {
	I = 1,
	J,
	Z,
	T,
	O,
	S,
	L
};

class Figure
{
private:
	Buffer figure;
	Image texture;
	FigureIndex index;
	__COORD coord{ 1, 5 };
	vector<__COORD> parts;

public:
	Figure();
	Figure(string filename, FigureIndex index);
	Figure(const Figure& figure);

	void Rotate();

	void LoadTextureToFigure();
	void CreateFigure();

	__COORD GetCoord() const;
	void SetCoord(size_t x, size_t y);
	void SetCoord(__COORD coord);

	Image& GetTexture();
	Buffer& GetBuffer();

	vector<__COORD>& GetParts();
	__COORD GetPart(size_t index);

	void LoadToBuffer(Buffer& buffer, __COORD coord);
	void LoadToBuffer(Buffer& buffer);
};
