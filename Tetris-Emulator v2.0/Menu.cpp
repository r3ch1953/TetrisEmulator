#include "Menu.h"
#include <iostream>

Menu::Menu()
{
	// empty
}

Menu::Menu(function<void(Menu& menu)> setup)
{
	if (setup != nullptr)
		this->setup = setup;
}

Menu::Menu(Cursor cursor, vector<Button> buttons, Buffer menu)
{
	this->cursor = cursor;
	this->buttons = buttons;
	this->menu = menu;

	this->cursor.SetButton(buttons[0]);
}

Cursor& Menu::GetCursor()
{
	return this->cursor;
}

Button& Menu::GetButton(size_t index)
{
	if (index < this->buttons.size())
		return this->buttons[index];
	return buttons[0];
}

Buffer& Menu::GetBuffer()
{
	return this->menu;
}

size_t Menu::GetButtonsVectorSize() const
{
	return this->buttons.size();
}

void Menu::AddButton(Button& button)
{
	button.GetLabel().SetColor(this->cursor.GetButtonDefaultColor());
	this->buttons.push_back(button);
}

void Menu::CursorPos(int key)
{
	size_t newIndex = 0;

	switch (key)
	{
	case 13:
		cursor.GetButton().StartButtonFunc();
		break;

	case 'w':
	case 'W':
		this->cursor.GetButton().GetLabel().SetColor(this->cursor.GetButtonDefaultColor());

		newIndex = (cursor.GetButtonPtr() - &this->buttons[0]) - 1;
		if (newIndex >= this->buttons.size())
			newIndex = 0;
		this->cursor.SetButton(this->buttons[newIndex]);
		break;

	case 'S':
	case 's':
		this->cursor.GetButton().GetLabel().SetColor(this->cursor.GetButtonDefaultColor());

		newIndex = (cursor.GetButtonPtr() - &this->buttons[0]) + 1;
		if (newIndex >= this->buttons.size())
			newIndex = 0;
		this->cursor.SetButton(this->buttons[newIndex]);
		break;
	}	
}

void Menu::LoadToBuffer(Buffer& buffer, __COORD coord)
{
	for (size_t i = 0; i < this->buttons.size(); i++)
		this->buttons[i].GetBuffer().Clear();

	this->cursor.LoadToBuffer(this->cursor.GetButton().GetBuffer(), __COORD{ this->GetCursor().GetButton().GetTexture().GetResolution().height / 2,
																		     this->GetCursor().GetButton().GetTexture().GetResolution().width});

	size_t prevHeight = 0;
	for (size_t i = 0; i < this->buttons.size(); i++)
	{
		this->buttons[i].LoadTextureToButton(__COORD{ 0,0 });
		this->buttons[i].LoadLabelToButton(__COORD{ this->buttons[i].GetTexture().GetResolution().height / 2,0 });
		this->buttons[i].LoadToBuffer(this->menu, __COORD{prevHeight, 0});
		prevHeight += this->buttons[i].GetTexture().GetResolution().height + 1;
	}

	if ((coord.y + this->menu.GetHeight()) > buffer.GetHeight() || (coord.x + this->menu.GetWidth()) > buffer.GetWidth())
	{
		cout << "Wrong X or Y! Error!\n";
		return;
	}

	for (size_t i = coord.y, menuI = 0; i < this->menu.GetHeight(); i++, menuI++)
	{
		for (size_t j = coord.x, menuJ = 0; j < this->menu.GetWidth(); j++, menuJ++)
		{
			buffer.Replace(this->menu.GetPixel(__COORD{ menuI, menuJ }), __COORD{ i,j });
		}
	}
}

void Menu::StartSetupFunc(Menu& menu)
{
	menu.setup(menu);
}
