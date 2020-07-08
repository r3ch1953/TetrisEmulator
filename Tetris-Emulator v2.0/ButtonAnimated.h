#pragma once
#include "Button.h"
#include "Animation.h"

class ButtonAnimated : public Button
{
private:
	Animation animation;
	size_t frameCounter = 0;

public:
	ButtonAnimated(Animation animation, function<void()> buttonFunc, string cursorTexture);

	Animation& GetAnimation();

	void LoadAnimationToButton(Buffer& buffer, __COORD coord);
	void LoadToBuffer(Buffer& buffer, __COORD coord) override;
	void LoadToBuffer(Buffer& buffer, __COORD coord, __COORD buttonStart);
};

