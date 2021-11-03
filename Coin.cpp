#include "Coin.h"

Coin::Coin(Point2f pos)
	: GameObject(pos)
{
	SetPosition(pos);
	SetType(OBJ_COIN);
	SetCollidable(true);
}

void Coin::Update(GameState& gState)
{
}

void Coin::Draw(GameState& gState) const
{
	float yWobble = sin(gState.time * PLAY_PI) * 2;
	if (b_collidable)
	{
		Play::DrawSprite(gState.sprites.coin, { m_pos.x - gState.camera.x, m_pos.y + yWobble - gState.camera.y }, (int)(3.f * gState.time));
	}
}

Coin* Coin::CreateCoin(Point2f pos)
{
	return new Coin(pos);
}
