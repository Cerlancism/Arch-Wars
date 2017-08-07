#pragma once
class Game
{

private:
	RenderWindow mWindow;
	int sizeX, sizeY;
public:
	Game(int sizeX, int sizeY, String title);
	~Game();
	void run();// to start the game
private:
	// Event Handling
	void processEvents();
	// game loop
	void update();
	// rendering of the game objects
	void render();

};

