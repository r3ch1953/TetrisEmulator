#pragma once
#include "Buffer.h"
#include "Label.h"
#include "Image.h"
#include <functional>
using namespace std;

class Button
{
protected:
	Buffer button;
	function<void()> buttonFunc = nullptr;

private:
	Label label;
	Image texture;

public:
	Button();
	Button(Label label, Image texture, function<void()> buttonFunc, string cursorTexture); // Cursor& cursor - GetTexture();
	Button(const Button& button);

	Label& GetLabel();
	Image& GetTexture();
	Buffer& GetBuffer();

	void SetButtonFunc(function <void()> buttonFunc);

	void LoadLabelToButton(__COORD coord);
	void LoadTextureToButton(__COORD coord);
	virtual void LoadToBuffer(Buffer& buffer, __COORD coord);

	void StartButtonFunc() const;
};
