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
private:
	Cursor cursor;
	vector<Button> buttons;
	Buffer menu;
	function<void(Menu& menu)> setup;

public:
	Menu(function<void(Menu& menu)> setup);
	Menu(Cursor cursor, vector<Button> buttons, Buffer menu);
	
	Cursor& GetCursor();
	Button& GetButton(size_t index);
	Buffer& GetBuffer();
	size_t GetButtonsVectorSize() const;

	void AddButton(Button& button);
	void CursorPos(int key);

	void LoadToBuffer(Buffer& buffer, __COORD coord);

	static void StartSetupFunc(Menu& menu);
};

