#include "Coin.h"

Coin::Coin(Point2f pos)
	: GameObject(pos)
{
	SetPosition(pos);
	SetType(OBJ_COIN);
	SetCollidable(true);
	SetHeight(37);
	SetWidth(40);
}

void Coin::Update(GameState& gState)
{
}

void Coin::Draw(GameState& gState) const
{
	// Add to pos.y to make the coins gently bounce up and down
	float yBounce = sin(gState.time * PLAY_PI) * 2;
	if (b_collidable)
	{
		Play::DrawSprite(gState.sprites.coin, { m_pos.x - gState.camera.x, m_pos.y + yBounce - gState.camera.y }, (int)(3.f * gState.time));
	}
}

Coin* Coin::CreateCoin(Point2f pos)
{
	return new Coin(pos);
}

bool Coin::IsColliding(GameObject* object1, GameObject* object2, bool isCrouching)
{
	PLAY_ASSERT_MSG(object1, "object1 cannot be null");
	PLAY_ASSERT_MSG(object2, "object2 cannot be null");
	// Object 1 bounding box parameters
	float object1_y = (isCrouching) ? object1->GetPosition().y + (object1->GetHeight() / 2.f) : object1->GetPosition().y;
	float object1_x = object1->GetPosition().x;
	float object1_yh = object1->GetPosition().y + object1->GetHeight();
	float object1_xw = object1->GetPosition().x + object1->GetWidth();
	// Object 2 bounding box parameters
	float object2_y = object2->GetPosition().y;
	float object2_x = object2->GetPosition().x;
	float object2_yh = object2->GetPosition().y + object2->GetHeight();
	float object2_xw = object2->GetPosition().x + object2->GetWidth();
	// Check if the player's bb is colliding with the coin's bb
	if (object1_x < object2_xw &&
		object1_xw > object2_x &&
		object1_y < object2_yh &&
		object1_yh > object2_y)
	{
		return true;
	}
	else
	{
		return false;
	}
}
