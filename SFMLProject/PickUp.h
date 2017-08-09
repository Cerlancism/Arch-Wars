#pragma once
#include "GameObject.h"

class PickUp : public GameObject
{
public:
	enum class Type { Health, Arrow };

private:
	const int HEALTHVALUE = 50;
	const int ARROWVALUE = 12;

	// The arena it exists in
	IntRect m_Arena;
	// How much is this pickup worth?
	int m_Value;
	bool m_Spawned = false;
	static float time;
	Type m_Type;

public:
	int Value;
	PickUp();
	PickUp(Type type);
	PickUp(Type type, int value);
	~PickUp();
	void SetType(PickUp::Type type);
	PickUp::Type GetType();
	void setArena(IntRect arena);
	void spawn();
	void spawn(Vector2f pos);
	int gotIt();
	bool IsSpawned();
	static bool RandownSpawn();
};

