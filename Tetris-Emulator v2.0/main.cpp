#include "Buffer.h"
#include "Image.h"
#include "Animation.h"
#include "Button.h"
#include "Menu.h"
#include <conio.h>
#include <iostream>
#include <Windows.h>

void setcur(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};

void MainMenu();

int main()
{
	MainMenu();

	return 0;
}

void MainMenu()
{
	Buffer buffer(Image::FindResolution("border.txt"));

	Animation mainMenuAnimation("mainMenuAnim.txt", 23);

	Image logo, border;

	logo.SetImage("logo.txt", Image::FindResolution("logo.txt"), 1);
	logo.SetColor(Color::LIGHTAQUA);

	border.SetImage("border.txt", Image::FindResolution("border.txt"), 1);

	border.LoadToBuffer(buffer, __COORD{ 0,0 });
	logo.LoadToBuffer(buffer, __COORD{ 1,2 });

	Menu menu([](Menu& menu) {
		Label label1("Play");
		Button button1(label1, Image::GetFrameFromFile("button.txt", Image::FindResolution("button.txt"), 1), nullptr);
		Label label3("Settings");
		Button button3(label3, Image::GetFrameFromFile("button.txt", Image::FindResolution("button.txt"), 1), nullptr);
		Label label2("Exit");
		Button button2(label2, Image::GetFrameFromFile("button.txt", Image::FindResolution("button.txt"), 1), []() { system("cls"); exit(0); });

		menu.AddButton(button1);
		menu.AddButton(button3);
		menu.AddButton(button2);

		menu.GetCursor().SetButton(menu.GetButton(0));
		menu.GetCursor().GetTexture().SetImage("cursor.txt", Image::FindResolution("cursor.txt"), 1);
		menu.GetCursor().GetBuffer().Resize(Image::FindResolution("cursor.txt"));
		menu.GetCursor().LoadTextureToCursor(__COORD{ 0,0 });

		Resolution newResolution{ 15,20 };

		menu.GetBuffer().Resize(newResolution);

		});

	menu.StartSetupFunc(menu);

	size_t counter = 1;

	while (true)
	{
		if (_kbhit())
			menu.CursorPos(_getch());

		if (counter > mainMenuAnimation.GetFramesCount())
			counter = 1;

		border.LoadToBuffer(buffer, __COORD{ 0,0 });
		mainMenuAnimation.LoadFrameToBuffer(buffer, __COORD{ 0,0 }, counter);
		logo.LoadToBuffer(buffer, __COORD{ 1,2 });
		menu.LoadToBuffer(buffer, __COORD{ 10,5 });

		counter++;
		buffer.Print();
		Sleep(10);
		setcur(0, 0);
	}
}
