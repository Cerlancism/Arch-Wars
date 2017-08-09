#pragma once
#include "GameObject.h"
class Player : public GameObject
{
private:
	float startSpeed = 200.0f;
	float speed;
	// What is the screen resolution
	Vector2f m_Resolution;
	// What size is the current arena
	IntRect m_Arena;
	// How big is each tile of the arena
	int m_TileSize;

	float health;

public:
	SoundBuffer shootSFX;

	Player();
	~Player();

	void Update() override;

	bool SetHealth(float hp);
	float GetHealth();

	void Spawn(IntRect arena, Vector2f resolution, int tileSize);
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();
	void Turn();
};

