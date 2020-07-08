#include "Button.h"
#include <iostream>
using namespace std;

Button::Button()
{
	// empty
}

Button::Button(Label label, Image texture, function<void()> buttonFunc, string cursorTexture)
{
	this->label.SetText(label.GetText());
	this->texture = texture;
	this->button.Resize(Resolution{ texture.GetResolution().height, texture.GetResolution().width + Image::FindResolution(cursorTexture).width});

	SetButtonFunc(buttonFunc);
}

Button::Button(const Button& button)
{
	this->button = button.button;
	this->buttonFunc = button.buttonFunc;
	this->label = button.label;
	this->texture = button.texture;
}

Label& Button::GetLabel()
{
	return this->label;
}

Image& Button::GetTexture()
{
	return this->texture;
}

Buffer& Button::GetBuffer()
{
	return this->button;
}

void Button::SetButtonFunc(function<void()> buttonFunc)
{
	this->buttonFunc = buttonFunc;
}

void Button::LoadLabelToButton(__COORD coord)
{
	this->label.LoadToBuffer(this->button, coord);
}

void Button::LoadTextureToButton(__COORD coord)
{
	this->texture.LoadToBuffer(this->button, __COORD{0, 0});
}

void Button::LoadToBuffer(Buffer& buffer, __COORD coord)
{
	if ((coord.y + this->button.GetHeight()) > buffer.GetHeight() || (coord.x + this->button.GetWidth()) > buffer.GetWidth())
	{
		cout << "Wrong X or Y! Error!\n";
		return;
	}

	for (size_t i = coord.y, buttonI = 0; buttonI < button.GetHeight(); i++, buttonI++)
	{
		for (size_t j = coord.x, buttonJ = 0; buttonJ < button.GetWidth(); j++, buttonJ++)
		{
			buffer.Replace(this->button.GetPixel(__COORD{ buttonI, buttonJ }), __COORD{ i,j });
		}
	}
}

void Button::StartButtonFunc() const
{
	this->buttonFunc();
}
