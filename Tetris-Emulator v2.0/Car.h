#pragma once
#include "Buffer.h"
#include "Image.h"

enum Side {
	UP,
	DOWN
};

class Car
{
protected:
	Buffer car;
	Image texture;
	Side side;
	size_t coordX = 2;

private:
	size_t score;

public:
	Car(Image texture);
	Car();

	Buffer& GetBuffer();
	Image& GetTexture();

	Side GetSide() const;
	void SetSide(Side side);

	size_t GetScore() const;
	void SetScore(size_t score);
	size_t GetCoordX() const;

	void Control(int key, Buffer& map);

	void LoadTextureToCar();

	virtual void LoadToBuffer(Buffer& buffer);
	void LoadToBuffer(Buffer& buffer, __COORD coord);

};

