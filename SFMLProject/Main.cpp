// SFMLProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game.h"
#include <windows.h>

int main()
{
	HWND consoleWindow = GetConsoleWindow();
	SetWindowPos(consoleWindow, 0, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Game::DebugLog("Loading Game");

	Vector2f ScreenSize;
	//Get the default screen resolution
	ScreenSize.x = VideoMode::getDesktopMode().width;
	ScreenSize.y = VideoMode::getDesktopMode().height;

	Game game(1600, 900, "Arch Wars", Style::Default, 60);
	game.run();
	return 0;
}

