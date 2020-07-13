#pragma once
#include "Buffer.h"
#include "Image.h"
#include "Button.h"

struct ButtonColor
{
	Color buttonSelected = Color::RED;
	Color buttonDefault = Color::BLUE;
};

class Cursor
{
protected:
	Image texture;
	Buffer cursor;
	ButtonColor buttonColor;

private:
	Button* button;

public:
	Cursor();
	Cursor(Button& button, Image texture);
	Cursor(const Cursor& cursor);

	Image& GetTexture();
	Button& GetButton();
	Button* GetButtonPtr() const;
	Buffer& GetBuffer();
	Color GetButtonSelectedColor();
	Color GetButtonDefaultColor();

	void SetButtonSelectedColor(Color color);
	void SetButtonDefaultColor(Color color);

	void SetButton(Button& button);
	
	void LoadTextureToCursor(__COORD coord);
	void LoadToBuffer(Buffer& buffer, __COORD coord);
};

