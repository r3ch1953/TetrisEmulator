#include "Label.h"
#include <iostream>
using namespace std;

Label::Label(char* text)
{
	SetText(text);
}

Label::Label(string text)
{
	SetText(text);
}

Label::Label(const Label& label)
{
	this->text = label.text;
	this->color = label.color;
	this->background = label.background;
}

Label::Label()
{
	text = "label";
}

string Label::GetText() const
{
	return text;
}

Color Label::GetColor() const
{
	return this->color;
}

Color Label::GetBackground() const
{
	return this->background;
}

size_t Label::GetLenght() const
{
	return text.length();
}

void Label::SetText(string text)
{
	if (!text.empty())
		this->text = text;
}

void Label::SetColor(Color color)
{
	this->color = color;
}

void Label::SetBackground(Color color)
{
	this->background = color;
}

void Label::LoadToBuffer(Buffer& buffer, __COORD coord)
{
	if ((coord.x + text.length()) > buffer.GetWidth() || coord.y > buffer.GetHeight())
	{
		cout << "Wrong X or Y! Error!\n";
		return;
	}

	for (size_t j = coord.x, labelJ = 0; labelJ < this->text.length(); j++, labelJ++)
	{
		if (this->text[labelJ] != '\n')
			buffer.Replace(Pixel{ this->text[labelJ], this->color, this->background }, __COORD{ coord.y,j });
	}
}

void Label::operator=(const Label& label)
{
	this->text = label.text;
	this->color = label.color;
	this->background = label.background;
}

