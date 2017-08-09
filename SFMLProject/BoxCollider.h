#pragma once
class BoxCollider
{
private:
	bool IsCollided();
	int colliderID;

public:
	//TODO more advanced collision management using layers
	enum class CollisionLayer{ PLAYER, ARROW, ENEMY, PICKUPS, NONE };
	CollisionLayer Layer;
	FloatRect Bounds;
	RectangleShape BoundsOutline;

	bool HasNewEnemyCollision();
	bool HasPickupCOllision();
	bool HasArrowCollision();
	bool HasPlayerCollision();

	static BoxCollider allcollider[];

	BoxCollider();
	~BoxCollider();
};

