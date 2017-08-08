#include "stdafx.h"
#include "Game.h"


Game::Game(int sizeX, int sizeY, String title, Uint32 style, Uint32 framerate):
	mainView(sf::FloatRect(0, 0, sizeX, sizeY)),
	hudView(sf::FloatRect(0, 0, sizeX, sizeY)),
	mWindow(sf::VideoMode(sizeX, sizeY), title, style),
	resolution(sizeX, sizeY)
{
	mWindow.setPosition(Vector2i(mWindow.getPosition().x, 50));
	mWindow.setMouseCursorVisible(false);
	mWindow.setFramerateLimit(framerate);

	//Load UI assets
	splashBackground = TextureHolder::GetTexture("graphics/background.png");
	menuBackground = TextureHolder::GetTexture("graphics/background.png");
	gameoverBackground = TextureHolder::GetTexture("graphics/background.png");
	uiBackground.setTexture(splashBackground);
	font.loadFromFile("fonts/mainfont.ttf");

	//Configure all the text
	splashText.setFont(font);
	splashText.setCharacterSize(125);
	splashText.setFillColor(Color::Black);
	splashText.setPosition(0, 0);
	splashText.setString("Arch Wars");

	menuText.setFont(font);
	menuText.setCharacterSize(125);
	menuText.setFillColor(Color::White);
	menuText.setPosition(0, sizeY/2);
	menuText.setString("Press Enter to Play...");

	//Load game assets
	tileBackground = TextureHolder::GetTexture("graphics/background_sheet.png");
	crosshairTexture = TextureHolder::GetTexture("graphics/crosshair.png");
	crosshairSprite.setTexture(crosshairTexture);
	crosshairSprite.setOrigin(25, 25);

	gameTimeTotal += clock.getElapsedTime();
	DebugLog("Loaded game: " + to_string(gameTimeTotal.asSeconds()));

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
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			mWindow.close();
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			mWindow.close();
		}

		// Start the game
		if (Keyboard::isKeyPressed(Keyboard::Return))
		{
			if (state == State::MENU )
			{
				WaveUp();
				state = State::PLAYING;
				DebugLog("Loaded Playing");
			}
		}
		if (event.type == Event::KeyReleased && !paused)
		{
			if (event.key.code == Keyboard::Return)
			{
				if (state == State::SPLASH)
				{
					LoadMenu();
				}
			}
		}
	}
}



// Handle update of the gameplay
void Game::update()
{
	gameTimeTotal += clock.restart();
	Time dt = clock.restart();
	float dtAsSeconds = dt.asSeconds();
	switch (state)
	{
	case Game::State::SPLASH:
		//fading in splash
		if (gameTimeTotal.asSeconds() < 3.0f)
		{
			uiBackground.setColor(Color(colorFade, colorFade, colorFade, 255));
			splashText.setColor(Color(colorFade, colorFade, colorFade, 255));
			colorFade = (colorFade + 2 < 255) ? colorFade + 2 : 255;
			DebugLog("fade value " + to_string(colorFade));
		}
		else
		{
			LoadMenu();
		}
		break;

	case Game::State::MENU:
		if (fadein)
		{
			menuText.setColor(Color(255, 255, 255, colorFade));
			colorFade = (colorFade + 5 < 255) ? colorFade + 5 : 255;
			fadein = (colorFade == 255) ? false : true;
		}
		else
		{
			menuText.setColor(Color(255, 255, 255, colorFade));
			colorFade = (colorFade - 5 > 0) ? colorFade - 5 : 0;
			fadein = (colorFade == 0) ? true : false;
		}
		break;

	case Game::State::PLAYING:
		//Fix mouse offset issue in window mode
		mouseScreenPosition = Vector2i(Mouse::getPosition().x - mWindow.getPosition().x, Mouse::getPosition().y - mWindow.getPosition().y);
		// Convert mouse position to world coordinates of mainView
		mouseWorldPosition = mWindow.mapPixelToCoords(mouseScreenPosition, mainView);
		// Set the crosshair to the mouse world location
		crosshairSprite.setPosition(mouseWorldPosition);
		break;

	case Game::State::PAUSED:
		break;

	case Game::State::LEVELING_UP:
		break;

	case Game::State::GAME_OVER:
		break;

	default:
		break;
	}
}

// Handle rendering for the game
void Game::render()
{
	switch (state)
	{
	case Game::State::SPLASH:
		mWindow.setView(hudView);
		mWindow.draw(uiBackground);
		mWindow.draw(splashText);
		break;

	case Game::State::MENU:
		mWindow.setView(hudView);
		mWindow.draw(uiBackground);
		mWindow.draw(menuText);
		break;

	case Game::State::PLAYING:
		mWindow.clear();
		mWindow.setView(mainView);
		mWindow.draw(background, &tileBackground);

		mWindow.draw(crosshairSprite);

		break;

	case Game::State::PAUSED:
		break;

	case Game::State::LEVELING_UP:
		break;

	case Game::State::GAME_OVER:
		break;

	default:
		break;
	}
	mWindow.display();
}

int Game::createBackground(VertexArray& rVA, IntRect arena)
{
	// How big is each tile/texture
	const int TILE_SIZE = 64;
	const int TILE_TYPES = 7;
	const int VERTS_IN_QUAD = 4;

	int worldWidth = arena.width / TILE_SIZE;
	int worldHeight = arena.height / TILE_SIZE;

	// What type of primitive are we using?
	rVA.setPrimitiveType(Quads);

	// Set the size of the vertex array
	rVA.resize(worldWidth * worldHeight * VERTS_IN_QUAD);

	// Start at the beginning of the vertex array
	int currentVertex = 0;

	for (int w = 0; w < worldWidth; w++)
	{
		for (int h = 0; h < worldHeight; h++)
		{
			// Position each vertex in the current quad
			rVA[currentVertex + 0].position = Vector2f(w * TILE_SIZE, h * TILE_SIZE);
			rVA[currentVertex + 1].position = Vector2f((w * TILE_SIZE) + TILE_SIZE, h * TILE_SIZE);
			rVA[currentVertex + 2].position = Vector2f((w * TILE_SIZE) + TILE_SIZE, (h * TILE_SIZE) + TILE_SIZE);
			rVA[currentVertex + 3].position = Vector2f((w * TILE_SIZE), (h * TILE_SIZE) + TILE_SIZE);

			// Define the position in the Texture to draw for current quad
			// Either mud, stone, grass or wall
			if (h == 0 || h == worldHeight - 1 || w == 0 || w == worldWidth - 1)
			{
				// Use the wall texture
				rVA[currentVertex + 0].texCoords = Vector2f(0, 0 + TILE_TYPES * TILE_SIZE);
				rVA[currentVertex + 1].texCoords = Vector2f(TILE_SIZE, 0 + TILE_TYPES * TILE_SIZE);
				rVA[currentVertex + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + TILE_TYPES * TILE_SIZE);
				rVA[currentVertex + 3].texCoords = Vector2f(0, TILE_SIZE + TILE_TYPES * TILE_SIZE);
			}
			else
			{
				// Use a random floor texture
				// mOrG stands for mud or grass. The name is arbitrary.
				int mOrG = (rand() % TILE_TYPES);
				//vetifcalOffset is a vertical reference point within the sprite sheet to the starting
				//height of the randomly chosen texture for the current quad.
				int verticalOffset = mOrG * TILE_SIZE;
				rVA[currentVertex + 0].texCoords = Vector2f(0, 0 + verticalOffset);
				rVA[currentVertex + 1].texCoords = Vector2f(TILE_SIZE, 0 + verticalOffset);
				rVA[currentVertex + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);
				rVA[currentVertex + 3].texCoords = Vector2f(0, TILE_SIZE + verticalOffset);
			}

			// Position ready for the next for vertices
			currentVertex = currentVertex + VERTS_IN_QUAD;
		}
	}

	return TILE_SIZE;
}

void Game::DebugLog(string log)
{
	cout << log << '\n';
}

void Game::LoadMenu()
{
	gameTimeTotal = Time::Zero;
	uiBackground.setTexture(menuBackground);
	uiBackground.setColor(Color(255, 255, 255, 255));
	colorFade = 255;
	state = State::MENU;
	gameTimeTotal += clock.restart();
	DebugLog("Loaded Menu: " + to_string(gameTimeTotal.asSeconds()));
}

void Game::WaveUp()
{
	wave++;
	arena.width = 512 * wave;
	arena.height = 512 * wave;
	arena.left = 0;
	arena.top = 0;

	int tileSize = createBackground(background, arena);

	clock.restart();
}

