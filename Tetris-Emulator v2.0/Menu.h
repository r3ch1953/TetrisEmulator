#pragma once
#include "Buffer.h"
#include "Button.h"
#include "Cursor.h"
#include "Label.h"
#include <functional>
#include <vector>
using namespace std;

class Menu
{
protected:
	Buffer menu;
	Cursor cursor;

private:
	vector<Button> buttons;
	function<void(Menu& menu)> setup;

public:
	Menu();
	Menu(function<void(Menu& menu)> setup);
	Menu(Cursor cursor, vector<Button> buttons, Buffer menu);
	
	Cursor& GetCursor();
	Button& GetButton(size_t index);
	Buffer& GetBuffer();
	virtual size_t GetButtonsVectorSize() const;

	void AddButton(Button& button);
	virtual void CursorPos(int key);

	virtual void LoadToBuffer(Buffer& buffer, __COORD coord);

	static void StartSetupFunc(Menu& menu);
};

