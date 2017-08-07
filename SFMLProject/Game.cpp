#include "stdafx.h"
#include "Game.h"


Game::Game(int sizeX, int sizeY, String title)
//Create the Rendering Window
//Set the video resolution for the game
	:mWindow(VideoMode(sizeX, sizeY), title), sizeX(sizeX), sizeY(sizeY)
{
}
Game::~Game()
{
}
// to start the game
void Game::run()
{
	while (mWindow.isOpen())
	{
		processEvents();
		update();
		render();
	}
}
// Handle events for the game
void Game::processEvents()
{
}
// Handle update of the gameplay
void Game::update()
{
}
// Handle rendering for the game
void Game::render()
{
}

