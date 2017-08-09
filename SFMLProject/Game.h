#include "stdafx.h"
#include "Player.h"
#include "Arrow.h"
#include "Enemy.h"
#include "PickUp.h"
#pragma once

class Game
{
private:
	int sizeX, sizeY;
	bool paused = false;
	int colorFade = 0;
	bool fadein = false;

	RenderWindow mWindow;
	// Create a an SFML View for the main action
	//Equivalent of Camera in Unity3D
	View mainView;
	// Create a view for the HUD
	View hudView;
	//Get the screen resolution and create an SFML windows
	Vector2f resolution;
	//Hold an instance of texture holder
	TextureHolder holder;

	//the Game will always be in one of these states
	enum class State { SPLASH, MENU, PLAYING, PAUSED, LEVELING_UP, GAME_OVER };
	State state = State::SPLASH;

	//Here is where we define the clock
	Clock clock;
	//How long the PLAYING state has been active
	Time gameTimeTotal;

	//Where is the mouse in relation to the world coordinate
	Vector2f mouseWorldPosition;
	//Where is the mouse in relation to the screen coordinate
	Vector2i mouseScreenPosition;

	Texture splashBackground;
	Texture menuBackground;
	Texture gameoverBackground;
	Sprite uiBackground;
	
	Texture tileBackground;
	Texture crosshairTexture;
	Sprite crosshairSprite;
	

	Font font;
	Text splashText;
	Text menuText;
	Text gameOverText;
	Text pauseText;
	Text levelupText;
	Text AmmoText;
	Text scoreText;

	//Gameworld
	IntRect arena;
	VertexArray background;

	//Gameplay
	int wave = 0;
	Player player;
	//Arrows
	Arrow arrows[ALLARROWS];
	int currentArrow = 0;
	int arrowsSpare = 10000;
	int arrowsInQuiver = 600;
	int quiverSize = 600;
	//Enemies
	int enemiesCount;
	int enemiesAliveCount;
	Enemy *Enemies = NULL;
	//Pickup
	PickUp pickups[10];
	int currentPickup = 0;


public:
	//Set the screen size and fullscreen mode and framerate
	Game(int sizeX, int sizeY, String title, Uint32 style, Uint32 framerate, Uint32 offsetY);
	~Game();
	void run();// to start the game
	static float deltaTime;


private:
	// Event Handling
	void processEvents();
	// game loop
	void update();
	// rendering of the game objects
	void render();

	int createBackground(VertexArray & rVA, IntRect arena);

	void LoadMenu();

	void WaveUp();

	Enemy* createHorde(int enemiescount, IntRect arena);

};


