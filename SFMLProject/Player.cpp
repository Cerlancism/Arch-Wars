#include "stdafx.h"
#include "Player.h"
#include "Game.h"


Player::Player()
{
	speed = startSpeed;
	SpriteSource.setTexture(TextureHolder::GetTexture("graphics/player.png"));
	CenterOrigin();
	Collider.Bounds = SpriteSource.getGlobalBounds();
	Collider.Layer = BoxCollider::CollisionLayer::PLAYER;
}


Player::~Player()
{}

void Player::Update()
{
	Turn();
}

bool Player::SetHealth(float hp)
{
	health += hp;
	return false;
}

float Player::GetHealth()
{
	return health;
}

void Player::Spawn(IntRect arena, Vector2f resolution, int tileSize)
{
	// Place the player in the middle of the arena
	SetPosition(arena.width / 2.0, arena.height / 2.0);

	// Copy the details of the arena to the player's m_Arena
	m_Arena.left = arena.left;
	m_Arena.width = arena.width;
	m_Arena.top = arena.top;
	m_Arena.height = arena.height;

	// Remember how big the tiles are in this arena
	m_TileSize = tileSize;

	// Strore the resolution for future use
	m_Resolution.x = resolution.x;
	m_Resolution.y = resolution.y;
}

void Player::MoveLeft()
{
	Vector2f position = GetPosition();
	(position.x <= m_Arena.left + m_TileSize) ?  false : SetPosition(Vector2f(position.x - speed * Game::deltaTime, position.y));
}

void Player::MoveRight()
{
	Vector2f position = GetPosition();
	(position.x >= m_Arena.width - m_TileSize) ? false : SetPosition(Vector2f(position.x + speed * Game::deltaTime, position.y));
}

void Player::MoveUp()
{
	Vector2f position = GetPosition();
	(position.y <= m_Arena.top + m_TileSize) ? false : SetPosition(Vector2f(position.x , position.y - speed * Game::deltaTime));
}

void Player::MoveDown()
{
	Vector2f position = GetPosition();
	(position.y >= m_Arena.height - m_TileSize) ? false : SetPosition(Vector2f(position.x, position.y + speed * Game::deltaTime));
}

void Player::Turn()
{
	// Calculate the angle the player is facing
	float angle = (atan2(Mouse::getPosition().y - m_Resolution.y / 2,
		Mouse::getPosition().x - m_Resolution.x / 2)
		* 180) / 3.141;
	SpriteSource.setRotation(angle);
}
