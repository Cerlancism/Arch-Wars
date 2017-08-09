#include "stdafx.h"
#include "PickUp.h"
#include "Game.h"

float PickUp::time = 0;

PickUp::PickUp()
{
	m_Spawned = false;
	SpriteSource.setTexture(TextureHolder::GetTexture("graphics/health_pickup.png"));
	SpriteSource.setOrigin(Vector2f(SpriteSource.getLocalBounds().width / 2.0f, SpriteSource.getLocalBounds().height / 2.0f));
	Collider.Bounds = SpriteSource.getGlobalBounds();
	Collider.Bounds.height = Collider.Bounds.width;
}

PickUp::PickUp(Type type)
{
	m_Type = type;
	switch (type)
	{
	case PickUp::Type::Health:
		m_Value = HEALTHVALUE;
		SpriteSource = Sprite(TextureHolder::GetTexture("graphics/health_pickup.png"));
		break;
	case PickUp::Type::Arrow:
		m_Value = ARROWVALUE;
		SpriteSource = Sprite(TextureHolder::GetTexture("graphics/ammo_pickup.png"));
		break;
	default:
		break;
	}
}

PickUp::PickUp(Type type, int value)
{
	m_Type = type;
	switch (type)
	{
	case PickUp::Type::Health:
		SpriteSource = Sprite(TextureHolder::GetTexture("graphics/health_pickup.png"));
		break;
	case PickUp::Type::Arrow:
		SpriteSource = Sprite(TextureHolder::GetTexture("graphics/ammo_pickup.png"));
		break;
	default:
		break;
	}
	m_Value = ARROWVALUE;
}

PickUp::~PickUp()
{}

void PickUp::SetType(PickUp::Type type)
{
	m_Type = type;
}

PickUp::Type PickUp::GetType()
{
	return m_Type;
}

void PickUp::setArena(IntRect arena)
{// Copy the details of the arena to the pickup's m_Arena
	//We trim the corner to prevent spawning at he border wall
	m_Arena.left = arena.left - 100;
	m_Arena.width = arena.width - 100;
	m_Arena.top = arena.top - 100;
	m_Arena.height = arena.height - 100;
}

void PickUp::spawn()
{
	switch (m_Type)
	{
	case PickUp::Type::Health:
		m_Value = HEALTHVALUE;
		SpriteSource = Sprite(TextureHolder::GetTexture("graphics/health_pickup.png"));
		break;
	case PickUp::Type::Arrow:
		m_Value = ARROWVALUE;
		SpriteSource = Sprite(TextureHolder::GetTexture("graphics/ammo_pickup.png"));
		break;
	default:
		break;
	}
	// Spawn at a random location
	//srand((int)time(0) / m_Type);
	int x = (rand() % m_Arena.width);
	//srand((int)time(0) * m_Type);
	int y = (rand() % m_Arena.height);

	// Not currently spawned
	//m_Spawned = false;
	m_Spawned = true;

	SetPosition(x, y);
}
void PickUp::spawn(Vector2f pos)
{
	switch (m_Type)
	{
	case PickUp::Type::Health:
		m_Value = HEALTHVALUE;
		SpriteSource = Sprite(TextureHolder::GetTexture("graphics/health_pickup.png"));
		break;
	case PickUp::Type::Arrow:
		m_Value = ARROWVALUE;
		SpriteSource = Sprite(TextureHolder::GetTexture("graphics/ammo_pickup.png"));
		break;
	default:
		break;
	}
	m_Spawned = true;
	SetPosition(pos);
}

int PickUp::gotIt()
{
	m_Spawned = false;
	return m_Value;
}

bool PickUp::IsSpawned()
{
	return m_Spawned;
}

bool newSec = false;
bool PickUp::RandownSpawn()
{
	if (int(time + Game::deltaTime) > (int)time )
	{
		newSec = true;
	}
	time += Game::deltaTime;
	int timeint = (int)time;
	if (newSec)
	{
		if (rand() % 30 == 0)
		{
			return true;
		}
		newSec = false;
	}
	return false;
}
