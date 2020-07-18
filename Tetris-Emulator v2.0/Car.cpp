#include "Car.h"

Car::Car(Image texture)
{
	this->texture = texture;
	this->car.Resize(this->texture.GetResolution());
	this->score = 0;
	this->side = Side::DOWN;
}

Car::Car()
{
	this->score = 0;
	this->side = Side::DOWN;
}

Buffer& Car::GetBuffer()
{
	return this->car;
}

Image& Car::GetTexture()
{
	return this->texture;
}

Side Car::GetSide() const
{
	return this->side;
}

void Car::SetSide(Side side)
{
	this->side = side;
}

size_t Car::GetScore() const
{
	return this->score;
}

void Car::SetScore(size_t score)
{
	this->score = score;
}

size_t Car::GetCoordX() const
{
	return this->coordX;
}

void Car::Control(int key, Buffer& map)
{
	switch (key)
	{
	case 'W':
	case 'w':
		SetSide(Side::UP);
		break;

	case 's':
	case 'S':
		SetSide(Side::DOWN);
		break;

	case 'd':
	case 'D':
		if (this->coordX < (map.GetWidth() - this->GetTexture().GetResolution().width))
			this->coordX++;
		break;

	case 'a':
	case 'A':
		if (this->coordX > 2)
			this->coordX--;
		break;
	}
}

void Car::LoadTextureToCar()
{
	this->texture.LoadToBuffer(this->car, __COORD{0, 0});
}

void Car::LoadToBuffer(Buffer& buffer)
{
	this->texture.LoadToBuffer(this->car, __COORD{0, 0});
	switch (this->side)
	{
	case Side::UP:
		for (size_t i = 1, carI = 0; carI < this->car.GetHeight(); i++, carI++)
		{
			for (size_t j = coordX, carJ = 0; carJ < this->car.GetWidth(); j++, carJ++)
			{
				buffer.Replace(this->car.GetPixel(__COORD{ carI, carJ }), __COORD{ i,j });
			}
		}
		break;
	case Side::DOWN:
		for (size_t i = 6, carI = 0; carI < this->car.GetHeight(); i++, carI++)
		{
			for (size_t j = coordX, carJ = 0; carJ < this->car.GetWidth(); j++, carJ++)
			{
				buffer.Replace(this->car.GetPixel(__COORD{ carI, carJ }), __COORD{ i,j });
			}
		}
		break;
	}
}

void Car::LoadToBuffer(Buffer& buffer, __COORD coord)
{
	this->texture.LoadToBuffer(this->car, __COORD{0, 0});
	switch (this->side)
	{
	case Side::UP:
		for (size_t i = coord.y, carI = 0; carI < this->car.GetHeight(); i++, carI++)
		{
			for (size_t j = coord.x, carJ = 0; carJ < this->car.GetWidth(); j++, carJ++)
			{
				buffer.Replace(this->car.GetPixel(__COORD{ carI, carJ }), __COORD{ i,j });
			}
		}
		break;
	case Side::DOWN:
		for (size_t i = coord.y, carI = 0; carI < this->car.GetHeight(); i++, carI++)
		{
			for (size_t j = coord.x, carJ = 0; carJ < this->car.GetWidth(); j++, carJ++)
			{
				buffer.Replace(this->car.GetPixel(__COORD{ carI, carJ }), __COORD{ i,j });
			}
		}
		break;
	}
}