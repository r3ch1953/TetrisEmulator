#pragma once
#include "ButtonAnimated.h"
#include "Menu.h"

enum Direction {
	UP,
	DOWN,
};
enum Progress {
	START,
	END
};

class MenuAnimated : public Menu
{
private:
	vector<ButtonAnimated> buttons;
	function<void(MenuAnimated& menu)> setup;
	Progress animation;
	int step = 0;

public:
	MenuAnimated(function<void(MenuAnimated& menu)> setup);

	ButtonAnimated& GetButton(size_t index);
	size_t GetButtonsVectorSize() const override;

	//void CursorPos(int key) override;
	void SwitchAnimation(Direction dir);

	void LoadToBuffer(Buffer& buffer, __COORD coord) override;
};

