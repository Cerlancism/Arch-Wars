#include "stdafx.h"
#include "BoxCollider.h"

BoxCollider::BoxCollider()
{

}


BoxCollider::~BoxCollider()
{

}

bool BoxCollider::HasNewEnemyCollision()
{
	return false;
}

bool BoxCollider::HasPickupCOllision()
{
	return false;
}

bool BoxCollider::HasArrowCollision()
{
	return false;
}

bool BoxCollider::HasPlayerCollision()
{
	return false;
}
