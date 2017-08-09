#pragma once
#include "BoxCollider.h"

class GameObject
{
	//Base class for main game objects such as player, enemy and pickups
protected:
	Transform transformer;

public:
	Sound SoundPlayer;
	BoxCollider Collider;
	Sprite SpriteSource;

	GameObject();
	~GameObject();

	Vector2f GetPosition();
	void SetPosition(Vector2f pos);
	void SetPosition(float x, float y);
	void CenterOrigin();
	virtual void Update();
};

