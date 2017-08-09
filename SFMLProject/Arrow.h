#pragma once
#include "GameObject.h"
class Arrow : public GameObject
{
private:
	bool inFlight = false;
	float speed = 1000;

	// What fraction of 1 pixel does the arrow travel, 
	// Horizontally and vertically each frame?
	// These values will be derived from m_BulletSpeed
	float m_BulletDistanceX;
	float m_BulletDistanceY;

	// Where is this arrow headed to?
	float m_XTarget;
	float m_YTarget;

	// Some boundaries so the arrow doesn't fly forever
	float m_MaxX;
	float m_MinX;
	float m_MaxY;
	float m_MinY;

	static float lastShoot;

public:
	static float Cooldown;

	Arrow();
	~Arrow();

	bool IsInFlight();

	void Stop();

	//check for cooldown
	static bool IsCooledDown();

	void Shoot(float startX, float startY, float targetX, float targetY);

	void Update() override;

	static void StaticUpdate();
};

