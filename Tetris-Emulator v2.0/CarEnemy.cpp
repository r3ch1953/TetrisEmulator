#include "CarEnemy.h"

CarEnemy::CarEnemy(Image texture) : Car(texture)
{
	// empty
}

bool CarEnemy::GetPop() const
{
	return this->pop;
}

bool CarEnemy::CheckCollison(Buffer& buffer, Car& car) const
{
	int enemyStart = buffer.GetWidth() - this->car.GetWidth() - step;
	int enemyEnd = enemyStart + this->car.GetWidth();
	int carStart = car.GetCoordX();
	int carEnd = carStart + car.GetTexture().GetResolution().width;

	if (car.GetSide() == GetSide())
	{
		if ((enemyStart <= carEnd && enemyStart >= carStart) ||
			(enemyEnd <= carEnd && enemyEnd >= carStart))
			return true;
	}
	return false;
}

void CarEnemy::LoadToBuffer(Buffer& buffer)
{
	this->texture.LoadToBuffer(this->car, __COORD{0, 0});

	__COORD start{ 0,0 };
	int newWidth = buffer.GetWidth() - this->car.GetWidth() - step;
	if (newWidth < 0)
	{
		start.x = -newWidth;
		newWidth = 1;
	}

	switch (this->side)
	{
	case Side::UP:
		for (size_t i = 1, carI = start.y; carI < this->car.GetHeight(); i++, carI++)
		{
			for (size_t j = newWidth, carJ = start.x; carJ < this->car.GetWidth(); j++, carJ++)
			{
				buffer.Replace(this->car.GetPixel(__COORD{ carI, carJ }), __COORD{ i,j });
			}
		}
		break;
	case Side::DOWN:
		for (size_t i = 6, carI = start.y; carI < this->car.GetHeight(); i++, carI++)
		{
			for (size_t j = newWidth, carJ = start.x; carJ < this->car.GetWidth(); j++, carJ++)
			{
				buffer.Replace(this->car.GetPixel(__COORD{ carI, carJ }), __COORD{ i,j });
			}
		}
		break;
	}

	this->step++;
	if (this->step > (buffer.GetWidth() + this->car.GetWidth()))
		this->pop = true;
}
