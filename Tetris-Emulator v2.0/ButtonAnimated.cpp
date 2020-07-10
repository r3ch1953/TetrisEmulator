#include "ButtonAnimated.h"
#include <iostream>
using namespace std;

ButtonAnimated::ButtonAnimated(Animation animation, function<void()> buttonFunc, string cursorTexture) : Button()
{
	this->animation = animation;
	this->button.Resize(Resolution{ animation.GetFrame(0).GetResolution().height, animation.GetFrame(0).GetResolution().width + Image::FindResolution(cursorTexture).width });

	SetButtonFunc(buttonFunc);
}

Animation& ButtonAnimated::GetAnimation()
{
	return this->animation;
}

void ButtonAnimated::LoadAnimationToButton(__COORD coord)
{
	this->animation.LoadFrameToBuffer(this->button, coord, frameCounter);

	this->frameCounter++;
	if (this->frameCounter > this->animation.GetFramesCount())
		this->frameCounter = 0;
}

void ButtonAnimated::LoadToBuffer(Buffer& buffer, __COORD coord)
{
	LoadAnimationToButton(__COORD{0, 0});

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

void ButtonAnimated::LoadToBuffer(Buffer& buffer, __COORD coord, __COORD buttonStart)
{
	LoadAnimationToButton(__COORD{0, 0});

	if ((coord.y + this->button.GetHeight()) > buffer.GetHeight() || (coord.x + this->button.GetWidth()) > buffer.GetWidth())
	{
		cout << "Wrong X or Y! Error!\n";
		return;
	}

	for (size_t i = coord.y, buttonI = buttonStart.y; buttonI < button.GetHeight(); i++, buttonI++)
	{
		for (size_t j = coord.x, buttonJ = buttonStart.x; buttonJ < button.GetWidth(); j++, buttonJ++)
		{
			buffer.Replace(this->button.GetPixel(__COORD{ buttonI, buttonJ }), __COORD{ i,j });
		}
	}
}
