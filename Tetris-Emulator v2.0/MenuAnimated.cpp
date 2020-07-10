#include "MenuAnimated.h"
#include <iostream>
using namespace std;

MenuAnimated::MenuAnimated(function<void(MenuAnimated& menu)>setup) : Menu()
{
	if (setup != nullptr)
		this->setup = setup;
}

ButtonAnimated& MenuAnimated::GetButton(size_t index)
{
	if (index < this->buttons.size())
		return this->buttons[index];
	return this->buttons[0];
}

size_t MenuAnimated::GetButtonsVectorSize() const
{
	return this->buttons.size();
}

//void MenuAnimated::CursorPos(int key)
//{
//	size_t newIndex = 0;
//
//	switch (key)
//	{
//	case 13:
//		cursor.GetButton().StartButtonFunc();
//		break;
//
//	case 'w':
//	case 'W':
//		this->cursor.GetButton().GetLabel().SetColor(this->cursor.GetButtonDefaultColor());
//
//		newIndex = (cursor.GetButtonPtr() - &this->buttons[0]) - 1;
//		if (newIndex >= this->buttons.size())
//			newIndex = 0;
//		this->cursor.SetButton(this->buttons[newIndex]);
//		break;
//
//	case 'S':
//	case 's':
//		this->cursor.GetButton().GetLabel().SetColor(this->cursor.GetButtonDefaultColor());
//
//		newIndex = (cursor.GetButtonPtr() - &this->buttons[0]) + 1;
//		if (newIndex >= this->buttons.size())
//			newIndex = 0;
//		this->cursor.SetButton(this->buttons[newIndex]);
//		break;
//	}
//}
//
//void MenuAnimated::SwitchAnimation(Direction dir)
//{
//	if (this->step == 0)
//		this->animation = Progress::START;
//	if (this->step == 13)
//		this->animation = Progress::END;
//
//
//}

void MenuAnimated::LoadToBuffer(Buffer& buffer, __COORD coord)
{
	for (size_t i = 0; i < this->buttons.size(); i++)
		this->buttons[i].GetBuffer().Clear();

	this->cursor.LoadToBuffer(this->cursor.GetButton().GetBuffer(), __COORD{ this->GetCursor().GetButton().GetTexture().GetResolution().height / 2,
																			 this->GetCursor().GetButton().GetTexture().GetResolution().width });

	//this->buttons[(cursor.GetButtonPtr() - &this->buttons[0]) - 1].LoadToBuffer(this->menu, __COORD{this->GetBuffer().GetHeight(), (this->GetBuffer().GetWidth() / 2) - (this->GetBuffer().GetWidth() / 2)});

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
