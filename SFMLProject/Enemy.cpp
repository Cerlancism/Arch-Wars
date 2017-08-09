#include "stdafx.h"
#include "Enemy.h"
#include "Game.h"


Enemy::Enemy()
{}


Enemy::~Enemy()
{}

bool Enemy::hit()
{
	m_Health--;

	if (m_Health <= 0)
	{
		// dead
		Vector2f oldpos = GetPosition();
		m_Alive = false;
		SpriteSource = Sprite(TextureHolder::GetTexture("graphics/dead.png"));
		SetPosition(oldpos);
		CenterOrigin();
		return true;
	}

	// injured but not dead yet
	return false;
}

bool Enemy::isAlive()
{
	return m_Alive;
}

void Enemy::Spawn(float x, float y, Type type, int i)
{ 
	switch (type)
	{
	case Enemy::Type::SLIME:
		SpriteSource = Sprite(TextureHolder::GetTexture("graphics/slime.png"));
		m_Speed = SLIME_SPEED;
		m_Health = SLIME_HEALTH;
		break;

	case Enemy::Type::MUSHROOM:
		SpriteSource = Sprite(TextureHolder::GetTexture("graphics/mushroom.png"));
		m_Speed = MUSHROOM_SPEED;
		m_Health = MUSHROOM_HEALTH;
		break;

	case Enemy::Type::STUMP:
		SpriteSource = Sprite(TextureHolder::GetTexture("graphics/stump.png"));
		m_Speed = STUMP_SPEED;
		m_Health = STUMP_HEALTH;
		break;

	default:
		break;
	}
	// Somewhere between 80 an 100
	float modifier = (rand() % MAX_VARRIANCE) + OFFSET;
	// Express as a fraction of 1
	modifier /= 100; // Now equals between .7 and 1
	m_Speed *= modifier;

	Collider.Bounds = SpriteSource.getGlobalBounds();
	CenterOrigin();
	SetPosition(x, y);
}

void Enemy::Update(Vector2f playerLocation)
{
	float elapsedTime = Game::deltaTime;
	float playerX = playerLocation.x;
	float playerY = playerLocation.y;

	// Update the LivingDead position variables
	if (playerX > GetPosition().x)
	{
		SetPosition(GetPosition().x + m_Speed * elapsedTime, GetPosition().y);
	}

	if (playerY > GetPosition().y)
	{
		SetPosition(GetPosition().x, GetPosition().y + m_Speed * elapsedTime);
	}

	if (playerX < GetPosition().x)
	{
		SetPosition(GetPosition().x - m_Speed * elapsedTime, GetPosition().y);
	}

	if (playerY < GetPosition().y)
	{
		SetPosition(GetPosition().x, GetPosition().y - m_Speed * elapsedTime);
	}
	// Face the sprite in the correct direction
	float angle = (atan2(playerY - GetPosition().y,
		playerX - GetPosition().x)
		* 180) / 3.141;
	SpriteSource.setRotation(angle);
}
