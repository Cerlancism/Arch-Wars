#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject()
{

}


GameObject::~GameObject()
{}

Vector2f GameObject::GetPosition()
{
	return SpriteSource.getPosition();
}

void GameObject::SetPosition(Vector2f pos)
{
	SpriteSource.setPosition(pos);
	//update collider position
	float left = SpriteSource.getPosition().x - SpriteSource.getTexture()->getSize().x / 2;
	float top = SpriteSource.getPosition().y - SpriteSource.getTexture()->getSize().y / 2;
	Collider.Bounds = FloatRect(left, top, SpriteSource.getTexture()->getSize().x, SpriteSource.getTexture()->getSize().y);
	//collider debug
	Collider.BoundsOutline.setSize(Vector2f(Collider.Bounds.width, Collider.Bounds.height));
	Collider.BoundsOutline.setOutlineColor(Color::Green);
	Collider.BoundsOutline.setFillColor(Color::Transparent);
	Collider.BoundsOutline.setOrigin(Collider.BoundsOutline.getLocalBounds().width / 2, Collider.BoundsOutline.getLocalBounds().height / 2);
	Collider.BoundsOutline.setOutlineThickness(2);
	Collider.BoundsOutline.setPosition(SpriteSource.getPosition());
}

void GameObject::SetPosition(float x, float y)
{
	SetPosition(Vector2f(x, y));
}

void GameObject::CenterOrigin()
{
	SpriteSource.setOrigin(Vector2f(SpriteSource.getLocalBounds().width / 2.0f, SpriteSource.getLocalBounds().height / 2.0f));
}

void GameObject::Update()
{

}
