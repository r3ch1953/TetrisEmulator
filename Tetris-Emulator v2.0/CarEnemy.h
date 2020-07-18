#pragma once
#include "Car.h"

class CarEnemy : public Car
{
private:
	size_t step = 0;
	bool pop = false;

public:
	CarEnemy(Image texture);

	bool GetPop() const;
	bool CheckCollison(Buffer& buffer, Car& car) const;

	void LoadToBuffer(Buffer& buffer) override;
};
