#pragma once
#include "GameObject.h"

class Enemy : GameObject
{
private:

public:
	Enemy();
	~Enemy();

	void Update() override;
};

