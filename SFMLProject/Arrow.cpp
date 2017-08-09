#include "stdafx.h"
#include "Arrow.h"
#include "Game.h"

float Arrow::lastShoot = 0;
float Arrow::DEFAULTRATE = 0.33f;
float Arrow::Cooldown = 0.33f;

Arrow::Arrow()
{
	SpriteSource.setTexture(TextureHolder::GetTexture("graphics/Arrow.png"));
	SpriteSource.setOrigin(Vector2f(SpriteSource.getLocalBounds().width / 2.0f, SpriteSource.getLocalBounds().height / 2.0f));
	Collider.Bounds = SpriteSource.getGlobalBounds();
	Collider.Bounds.height = Collider.Bounds.width;
}


Arrow::~Arrow()
{}

bool Arrow::IsInFlight()
{
	return inFlight;
}

void Arrow::Stop()
{
	inFlight = false;
}

bool Arrow::IsCooledDown()
{
	if (lastShoot <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Arrow::UpgradeRate()
{
	Cooldown = Cooldown * 0.8f;
}

void Arrow::Reset()
{
	Cooldown = DEFAULTRATE;
}

void Arrow::Shoot(float startX, float startY, float targetX, float targetY)
{
	lastShoot = Cooldown;
	// Keep track of the bullet
	inFlight = true;
	SpriteSource.setPosition(startX, startY);

	// Calculate the gradient of the flight path
	float gradient = (startX - targetX) / (startY - targetY);

	// Any gradient less than zero needs to be negative
	if (gradient < 0)//Just to make everything positive
	{
		gradient *= -1;
	}
	// Calculate the ratio between x and t
	float ratioXY = speed / (1 + gradient);

	// Set the "speed" horizontally and vertically
	m_BulletDistanceY = ratioXY;
	m_BulletDistanceX = ratioXY * gradient;

	// Point the bullet in the right direction
	if (targetX < startX)
	{
		m_BulletDistanceX *= -1;
	}

	if (targetY < startY)
	{
		m_BulletDistanceY *= -1;
	}

	// Finally, assign the results to the
	// member variables
	m_XTarget = targetX;
	m_YTarget = targetY;

	// Set a max range of 1000 pixels
	float range = 1000;
	m_MinX = startX - range;
	m_MaxX = startX + range;
	m_MinY = startY - range;
	m_MaxY = startY + range;
}

void Arrow::Update()
{
	// Update the bullet position variables
	SpriteSource.setPosition(
		SpriteSource.getPosition().x + m_BulletDistanceX * Game::deltaTime,
		SpriteSource.getPosition().y + m_BulletDistanceY * Game::deltaTime);

	//update collider position
	float left = SpriteSource.getPosition().x - SpriteSource.getTexture()->getSize().x / 2;
	float top = SpriteSource.getPosition().y - SpriteSource.getTexture()->getSize().y / 2;
	Collider.Bounds = FloatRect(left, top, SpriteSource.getTexture()->getSize().x, SpriteSource.getTexture()->getSize().y);
	Collider.Bounds.height = Collider.Bounds.width;

	// Has the bullet gone out of range?
	if (SpriteSource.getPosition().x < m_MinX || SpriteSource.getPosition().x > m_MaxX ||
		SpriteSource.getPosition().y < m_MinY || SpriteSource.getPosition().y > m_MaxY)
	{
		inFlight = false;
	}
}

void Arrow::StaticUpdate()
{
	lastShoot = (lastShoot > 0) ? lastShoot - Game::deltaTime : 0;
}
