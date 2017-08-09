// SFMLProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game.h"
#include <windows.h>

int main()
{
	//Debug set up
	HWND consoleWindow = GetConsoleWindow();
	SetWindowPos(consoleWindow, 0, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	Debug::Log("Loading Game");

	Vector2f ScreenSize;
	//Get the default screen resolution
	ScreenSize.x = VideoMode::getDesktopMode().width;
	ScreenSize.y = VideoMode::getDesktopMode().height;

	Game game(1280, 720, "Arch Wars", Style::Default, 60, 50);
	game.run();
	return 0;
}

