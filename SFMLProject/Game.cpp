#include "stdafx.h"
#include "Game.h"

float Game::deltaTime = 0;

Game::Game(int sizeX, int sizeY, String title, Uint32 style, Uint32 framerate, Uint32 offsetY):
	mainView(sf::FloatRect(0, 0, sizeX, sizeY)),
	hudView(sf::FloatRect(0, 0, sizeX, sizeY)),
	mWindow(sf::VideoMode(sizeX, sizeY), title, style),
	resolution(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height - ((VideoMode::getDesktopMode().height - sizeY) / 2 + offsetY))
{
	srand(time(NULL));
	mWindow.setPosition(Vector2i(mWindow.getPosition().x, offsetY));
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
	crosshairSprite.setOrigin(23, 23);

	gameTimeTotal += clock.getElapsedTime();
	Debug::Log("Loaded game: " + to_string(gameTimeTotal.asSeconds()));

}

Game::~Game()
{
	delete[] Enemies;
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
				Debug::Log("Loaded Playing");
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

	if (state == State::PLAYING)
	{
		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			player.MoveUp();
		}

		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			player.MoveDown();
		}

		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			player.MoveLeft();
		}

		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			player.MoveRight();
		}

		// Fire a arrow
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (Arrow::IsCooledDown() && arrowsInQuiver > 0)
			{
				// Pass the centre of the player and the centre of the crosshair
				// to the shoot function
				arrows[currentArrow].Shoot(player.SpriteSource.getPosition().x, player.SpriteSource.getPosition().y, mouseWorldPosition.x, mouseWorldPosition.y);
				//rotation arrow
				float angle = (atan2(Mouse::getPosition().y - resolution.y / 2 ,
					Mouse::getPosition().x - resolution.x / 2)
					* 180 + 270) / 3.141;
				arrows[currentArrow].SpriteSource.setRotation(angle);
				currentArrow = (currentArrow + 1 == ALLARROWS) ? 0 : currentArrow + 1;
			}
		}// End fire a bullet

	}
}



// Handle update of the gameplay
void Game::update()
{
	Time dt = clock.restart();
	gameTimeTotal += dt;
	deltaTime = dt.asSeconds();
	switch (state)
	{
	case Game::State::SPLASH:
		//fading in splash
		if (gameTimeTotal.asSeconds() < 3.0f)
		{
			uiBackground.setColor(Color(colorFade, colorFade, colorFade, 255));
			splashText.setColor(Color(colorFade, colorFade, colorFade, 255));
			colorFade = (colorFade + 2 < 255) ? colorFade + 2 : 255;
			Debug::Log("fade value " + to_string(colorFade));
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
		//Center Camera
		mainView.setCenter(player.SpriteSource.getPosition());

		player.Update();
		Arrow::StaticUpdate();
		for (int i = 0; i < ALLARROWS; i++)
		{
			if (arrows[i].IsInFlight())
			{
				arrows[i].Update();
			}
		}
		for (int i = 0; i < enemiesCount; i++)
		{
			if (Enemies[i].isAlive())
			{
				Enemies[i].Update(player.GetPosition());
			}
		}
		for each (Arrow &arrow in arrows)
		{
			if (arrow.IsInFlight())
			{
				for (int i = 0; i < enemiesCount; i++)
				{
					if (Enemies[i].isAlive())
					{
						if (Enemies[i].Collider.Bounds.intersects(arrow.Collider.Bounds))
						{
							arrow.Stop();
							if (Enemies[i].hit())
							{
								enemiesAliveCount--;
								//33% chance spawning drops
								if (rand() % 3 == 0)
								{
									Debug::Log(to_string(rand() % 2));
									PickUp::Type type = (rand() % 2 == 0) ? PickUp::Type::Arrow : PickUp::Type::Health;
									pickups[currentPickup].SetType(type);
									pickups[currentPickup].setArena(arena);
									pickups[currentPickup].spawn(Enemies[i].GetPosition()- Enemies[i].SpriteSource.getOrigin());
									currentPickup = (currentPickup + 1 >= enemiesCount) ? 0 : currentPickup + 1;
								}
								if (enemiesAliveCount == 0)
								{
									state = State::LEVELING_UP;
								}
							}
						}
					}
				}
			}
		}
		for each (PickUp &pickup in pickups)
		{
			if (player.Collider.Bounds.intersects(pickup.Collider.Bounds))
			{
				PickUp::Type type = pickup.GetType();
				switch (type)
				{
				case PickUp::Type::Health:
					pickup.gotIt();
					break;
				case PickUp::Type::Arrow:
					pickup.gotIt();
					break;
				default:
					break;
				}
			}
		}
		if (PickUp::RandownSpawn())
		{
			PickUp::Type type = (rand() % 2 == 0) ? PickUp::Type::Arrow : PickUp::Type::Health;
			pickups[currentPickup].SetType(type);
			pickups[currentPickup].setArena(arena);
			pickups[currentPickup].spawn();
			currentPickup = (currentPickup + 1 >= enemiesCount) ? 0 : currentPickup + 1;
		}
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
	int c = 0;
	RectangleShape rectangle;
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

		for (int i = 0; i < enemiesCount; i++)
		{
			mWindow.draw(Enemies[i].SpriteSource);
			
			player.Collider.Bounds.intersects(Enemies[i].Collider.Bounds) ? player.Collider.BoundsOutline.setOutlineColor(Color::Red) : player.Collider.BoundsOutline.getOutlineColor();
			for (int ii = 0; ii < ALLARROWS; ii++)
			{
				if (arrows[ii].IsInFlight())
				{
					arrows[ii].Collider.Bounds.intersects(Enemies[i].Collider.Bounds) ? Enemies[i].Collider.BoundsOutline.setOutlineColor(Color::Red) : false;
				}
			}
			mWindow.draw(Enemies[i].Collider.BoundsOutline);
		}

		mWindow.draw(player.SpriteSource);
		
		mWindow.draw(player.Collider.BoundsOutline);
		for (int i = 0; i < ALLARROWS; i++)
		{
			if (arrows[i].IsInFlight())
			{
				mWindow.draw(arrows[i].SpriteSource);
				mWindow.draw(arrows[i].Collider.BoundsOutline);
			}
		}
		for (int i = 0; i < 10; i++)
		{
			if (pickups[i].IsSpawned())
			{
				mWindow.draw(pickups[i].SpriteSource);
			}
		}

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

void Game::LoadMenu()
{
	gameTimeTotal = Time::Zero;
	uiBackground.setTexture(menuBackground);
	uiBackground.setColor(Color(255, 255, 255, 255));
	colorFade = 255;
	state = State::MENU;
	gameTimeTotal += clock.restart();
	Debug::Log("Loaded Menu: " + to_string(gameTimeTotal.asSeconds()));
}

void Game::WaveUp()
{
	wave++;
	arena.width = 768 * wave;
	arena.height = 768 * wave;
	arena.left = 0;
	arena.top = 0;
	int tileSize = createBackground(background, arena);

	player.Spawn(arena, resolution, tileSize);
	enemiesCount = 5 * wave;
	delete[] Enemies;
	Enemies = createHorde(enemiesCount, arena);
	enemiesAliveCount = enemiesCount;
	pickups[enemiesCount];
	clock.restart();
}

Enemy* Game::createHorde(int enemiescount, IntRect arena)
{
	Enemy* enemies = new Enemy[enemiesCount];

	int maxY = arena.height - 20;
	int minY = arena.top + 20;
	int maxX = arena.width - 20;
	int minX = arena.left + 20;

	for (int i = 0; i < enemiesCount; i++)
	{

		// Which side should the LivingDead spawn
		int side = (rand() % 4);
		float x, y;

		switch (side)
		{
		case 0:
			// left
			x = minX;
			y = (rand() % maxY) + minY;
			break;

		case 1:
			// right
			x = maxX;
			y = (rand() % maxY) + minY;
			break;

		case 2:
			// top
			x = (rand() % maxX) + minX;
			y = minY;
			break;

		case 3:
			// bottom
			x = (rand() % maxX) + minX;
			y = maxY;
			break;
		}

		// Slime, Mushroom or Stumps
		Enemy::Type type = static_cast<Enemy::Type>(rand() % 3);

		// Spawn the new LivingDead into the array
		enemies[i].Spawn(x, y, type, i);
	}
	return enemies;
}

