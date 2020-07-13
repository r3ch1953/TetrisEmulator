#include "Buffer.h"
#include "Image.h"
#include "Animation.h"
#include "Button.h"
#include "Menu.h"
#include "Car.h"
#include "Map.h"
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
void Racing();
void SelectGameMenu();

int main()
{
	MainMenu();

	return 0;
}

void MainMenu()
{
	Buffer buffer(Image::FindResolution("MM_border.txt"));

	Animation mainMenuAnimation("MM_anim.txt", 23);

	Image logo, border;

	Label control1("W/S - UP/DOWN,");
	Label control2("Enter - Confirm.");
	control1.SetColor(Color::GRAY);
	control2.SetColor(Color::GRAY);

	logo.SetImage("MM_logo.txt", Image::FindResolution("MM_logo.txt"), 1);
	logo.SetColor(Color::LIGHTAQUA);

	border.SetImage("MM_border.txt", Image::FindResolution("MM_border.txt"), 1);

	Menu menu([](Menu& menu) {
		Label label1("Play");
		Button button1(label1, Image::GetFrameFromFile("MM_button.txt", Image::FindResolution("MM_button.txt"), 1), SelectGameMenu, "MM_cursor.txt");
		Label label3("Settings");
		Button button3(label3, Image::GetFrameFromFile("MM_button.txt", Image::FindResolution("MM_button.txt"), 1), nullptr, "MM_cursor.txt");
		Label label2("Exit");
		Button button2(label2, Image::GetFrameFromFile("MM_button.txt", Image::FindResolution("MM_button.txt"), 1), []() { system("cls"); exit(0); }, "MM_cursor.txt");

		menu.AddButton(button1);
		menu.AddButton(button3);
		menu.AddButton(button2);

		menu.GetCursor().SetButton(menu.GetButton(0));
		menu.GetCursor().GetTexture().SetImage("MM_cursor.txt", Image::FindResolution("MM_cursor.txt"), 1);
		menu.GetCursor().GetBuffer().Resize(Image::FindResolution("MM_cursor.txt"));
		menu.GetCursor().LoadTextureToCursor(__COORD{ 0,0 });

		Resolution newResolution{ 15,20 };

		menu.GetBuffer().Resize(newResolution);

		});

	Menu::StartSetupFunc(menu);

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
		control1.LoadToBuffer(buffer, __COORD{ 23, 2 });
		control2.LoadToBuffer(buffer, __COORD{ 24, 2 });


		counter++;
		buffer.Print();
		Sleep(10);
		setcur(0, 0);
	}
	system("cls");
}

void Racing()
{
	system("cls");

	Label scoreStr("Score: ");
	Map map(Image::GetFrameFromFile("R_scoreBoard.txt", Image::FindResolution("R_scoreBoard.txt"), 1),
			Image::GetFrameFromFile("R_gameField.txt", Image::FindResolution("R_gameField.txt"), 1),
			scoreStr,
			Image::GetFrameFromFile("R_cars.txt", Image::FindResolution("R_cars.txt"), 1));

	Buffer buffer(Resolution{ Image::FindResolution("R_gameField.txt").height + Image::FindResolution("R_scoreBoard.txt").height, Image::FindResolution("R_gameField.txt").width });
	while (!map.GetGameOver())
	{
		map.LoadToBuffer(buffer, __COORD{ 0,0 });

		if (_kbhit())
			map.Control(_getch());

		buffer.Print();
		setcur(0, 0);
	}

	buffer.Clear();
	map.ShowGameOverScreen(buffer);
	buffer.Print();
	system("pause");
	system("cls");
}

void SelectGameMenu()
{
	Buffer buffer(Image::FindResolution("MM_border.txt"));

	Animation mainMenuAnimation("MM_anim.txt", 23);

	Image logo, border;

	Label control1("W/S - UP/DOWN,");
	Label control2("Enter - Confirm.");
	control1.SetColor(Color::GRAY);
	control2.SetColor(Color::GRAY);

	logo.SetImage("MM_logo.txt", Image::FindResolution("MM_logo.txt"), 1);
	logo.SetColor(Color::LIGHTAQUA);

	border.SetImage("MM_border.txt", Image::FindResolution("MM_border.txt"), 1);

	bool exit = false;
	Menu menu([&exit](Menu& menu) {
		Label label1("Racing");
		Button button1(label1, Image::GetFrameFromFile("MM_button.txt", Image::FindResolution("MM_button.txt"), 1), Racing, "MM_cursor.txt");
		Label label2("Tetris");
		Button button2(label2, Image::GetFrameFromFile("MM_button.txt", Image::FindResolution("MM_button.txt"), 1), [&exit]() { exit = true; }, "MM_cursor.txt");
		Label label3("Ping Pong");
		Button button3(label3, Image::GetFrameFromFile("MM_button.txt", Image::FindResolution("MM_button.txt"), 1), [&exit]() { exit = true; }, "MM_cursor.txt");
		Label label4("Return");
		Button button4(label4, Image::GetFrameFromFile("MM_button.txt", Image::FindResolution("MM_button.txt"), 1), [&exit]() { exit = true; }, "MM_cursor.txt");
		
		menu.AddButton(button1);
		menu.AddButton(button2);
		menu.AddButton(button3);
		menu.AddButton(button4);

		menu.GetCursor().SetButton(menu.GetButton(0));
		menu.GetCursor().GetTexture().SetImage("MM_cursor.txt", Image::FindResolution("MM_cursor.txt"), 1);
		menu.GetCursor().GetBuffer().Resize(Image::FindResolution("MM_cursor.txt"));
		menu.GetCursor().LoadTextureToCursor(__COORD{ 0,0 });

		Resolution newResolution{ 17,20 };

		menu.GetBuffer().Resize(newResolution);

		});

	Menu::StartSetupFunc(menu);

	size_t counter = 1;


	while (!exit)
	{
		if (_kbhit())
			menu.CursorPos(_getch());

		if (counter > mainMenuAnimation.GetFramesCount())
			counter = 1;

		border.LoadToBuffer(buffer, __COORD{ 0,0 });
		mainMenuAnimation.LoadFrameToBuffer(buffer, __COORD{ 0,0 }, counter);
		logo.LoadToBuffer(buffer, __COORD{ 1,2 });
		menu.LoadToBuffer(buffer, __COORD{ 10,5 });
		control1.LoadToBuffer(buffer, __COORD{ 23, 2 });
		control2.LoadToBuffer(buffer, __COORD{ 24, 2 });


		counter++;
		buffer.Print();
		Sleep(10);
		setcur(0, 0);
	}
	system("cls");
}
