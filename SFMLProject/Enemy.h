#pragma once
#include "GameObject.h"
class Enemy : public GameObject
{
private:
	// How fast is each Enemy type?
	const float SLIME_SPEED = 80;
	const float MUSHROOM_SPEED = 50;
	const float STUMP_SPEED = 30;

	// How tough is each Enemy type
	const float SLIME_HEALTH = 3;
	const float MUSHROOM_HEALTH = 2;
	const float STUMP_HEALTH = 5;

	// Make each Enemy vary its speed slightly
	const int MAX_VARRIANCE = 30;
	const int OFFSET = 101 - MAX_VARRIANCE;

	// How fast can this one run/crawl?
	float m_Speed;

	// How much health has it got?
	float m_Health;

	// Is it still alive?
	bool m_Alive;

public:
	enum class Type { SLIME, MUSHROOM, STUMP};
	Enemy();
	~Enemy();

	// Handle when a bullet hits a Enemy
	bool hit();
	// Find out if the Enemy is alive
	bool isAlive();
	void Spawn(float x, float y, Type type, int i);
	void Update(Vector2f playerLocation);
};

