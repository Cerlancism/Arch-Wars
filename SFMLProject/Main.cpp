// SFMLProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game.h"
#include <windows.h>
#include <iostream>

int main()
{
	//Debug set up to top left for a better view
	HWND consoleWindow = GetConsoleWindow();
	SetWindowPos(consoleWindow, 0, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	

	bool valid = false;
	while (!valid)
	{
		cout << "Select Screen mode: 1 - 1280x720, 2 - Fullscreen, 3 - Windowed ScreenSize\n";
		string input;
		std::getline(std::cin, input);

		if (input == "1" || input == "2" || input == "3")
		{
			Debug::Log("Loading Game");
			valid = true;
			if (input == "1")
			{
				Game game(1280, 720, "Arch Wars", Style::Default, 60, 50);
				game.run();
			}
			if (input == "2")
			{
				Vector2f ScreenSize;
				//Get the default screen resolution
				ScreenSize.x = VideoMode::getDesktopMode().width;
				ScreenSize.y = VideoMode::getDesktopMode().height;
				Game game(ScreenSize.x, ScreenSize.y, "Arch Wars", Style::Fullscreen, 60, 0);
				game.run();
			}
			if (input == "3")
			{
				Vector2f ScreenSize;
				//Get the default screen resolution
				ScreenSize.x = VideoMode::getDesktopMode().width;
				ScreenSize.y = VideoMode::getDesktopMode().height;
				Game game(ScreenSize.x, ScreenSize.y, "Arch Wars", Style::Default, 60, 0);
				game.run();
			}
		}
		else
		{
			valid == false;
		}
	}

	return 0;
}

