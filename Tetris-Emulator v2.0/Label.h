#pragma once
#include "Buffer.h"
#include <string>
using namespace std;

class Label
{
private:
	string text;
	Color color = Color::WHITE;
	Color background = Color::BLACK;

public:
	Label(char* text);
	Label(string text);
	Label(const Label& label);
	Label();

	string GetText() const;
	Color GetColor() const;
	Color GetBackground() const;
	size_t GetLenght() const;

	void Clear();
	void SetText(string text);
	void SetColor(Color color);
	void SetBackground(Color color);
	
	void LoadToBuffer(Buffer& buffer, __COORD coord);

	void operator = (const Label& label);
};

