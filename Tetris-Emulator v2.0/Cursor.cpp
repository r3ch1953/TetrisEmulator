#include "Cursor.h"
#include <iostream>

Cursor::Cursor()
{
	button = nullptr;
}

Cursor::Cursor(Button& button, Image texture)
{
	this->button = &button;
	this->texture = texture;
	this->cursor.Resize(texture.GetResolution());
}

Cursor::Cursor(const Cursor& cursor)
{
	this->button = cursor.button;
	this->texture = cursor.texture;
	this->cursor = cursor.cursor;
}

Image& Cursor::GetTexture()
{
	return this->texture;
}

Button& Cursor::GetButton()
{
	return *(this->button);
}

Button* Cursor::GetButtonPtr() const
{
	return this->button;
}

Buffer& Cursor::GetBuffer()
{
	return this->cursor;
}

Color Cursor::GetButtonSelectedColor()
{
	return this->buttonColor.buttonSelected;
}

Color Cursor::GetButtonDefaultColor()
{
	return this->buttonColor.buttonDefault;
}

void Cursor::SetButtonSelectedColor(Color color)
{
	this->buttonColor.buttonSelected = color;
}

void Cursor::SetButtonDefaultColor(Color color)
{
	this->buttonColor.buttonDefault = color;
}

void Cursor::SetButton(Button& button)
{
	this->button = &button;
	this->button->GetLabel().SetColor(this->buttonColor.buttonSelected);
}

void Cursor::LoadTextureToCursor(__COORD coord)
{
	texture.LoadToBuffer(this->cursor, coord);
}

void Cursor::LoadToBuffer(Buffer& buffer, __COORD coord)
{
	if ((coord.y + this->cursor.GetHeight()) > buffer.GetHeight() || (coord.x + this->cursor.GetWidth()) > buffer.GetWidth())
	{
		cout << "Wrong X or Y! Error!\n";
		return;
	}

	for (size_t i = coord.y, cursorI = 0; cursorI < cursor.GetHeight(); i++, cursorI++)
	{
		for (size_t j = coord.x, cursorJ = 0; cursorJ < cursor.GetWidth(); j++, cursorJ++)
		{
			buffer.Replace(this->cursor.GetPixel(__COORD{ cursorI, cursorJ }), __COORD{ i,j });
		}
	}
}