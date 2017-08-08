#pragma once
#include "AudioSource.h"
#include "BoxCollider.h"

class GameObject
{
protected:
	Vector2f position;

public:
	AudioSource audio;
	BoxCollider collider;
	Sprite sprite;

	GameObject();
	~GameObject();

	virtual void Update();

};

