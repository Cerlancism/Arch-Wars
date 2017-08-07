// SFMLProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game.h"


int main()
{
	Game game(1280, 768, "Testing");
	game.run();
	return 0;
}

