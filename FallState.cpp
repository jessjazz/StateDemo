#include "FallState.h"
#include "Player.h"
#include "IdleState.h"

PlayerState* FallRightState::HandleInput(Player& player)
{
	if (player.IsGrounded())
	{
		player.SetDrawState(State::STATE_IDLE);
		return new IdleRightState;
	}
	return nullptr;
}

void FallRightState::StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const
{
	int spriteId = gState.sprites.fallRight;
	player.SetHeight(Play::GetSpriteHeight(spriteId));
	player.SetWidth(Play::GetSpriteWidth(spriteId));
	
	Point2f currentPos = player.GetPosition();;

	player.SetVelocity(player.GetVelocity() + player.GetGravity());
	player.SetPosition(currentPos + player.GetVelocity());

	for (GameObject* p : map)
	{
		if (player.IsStandingOn(&player, p))
		{
			player.SetGrounded(true);
		}
	}

	if (player.GetPosition().y > DISPLAY_HEIGHT)
	{
		player.SetDead(true);
	}
}

PlayerState* FallLeftState::HandleInput(Player& player)
{
	if (player.IsGrounded())
	{
		player.SetDrawState(State::STATE_IDLE_LEFT);
		return new IdleLeftState;
	}
	return nullptr;
}

void FallLeftState::StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const
{
	int spriteId = gState.sprites.fallLeft;
	player.SetHeight(Play::GetSpriteHeight(spriteId));
	player.SetWidth(Play::GetSpriteWidth(spriteId));

	Point2f currentPos = player.GetPosition();;

	player.SetVelocity(player.GetVelocity() + player.GetGravity());
	player.SetPosition(currentPos + player.GetVelocity());

	for (GameObject* p : map)
	{
		if (player.IsStandingOn(&player, p))
		{
			player.SetGrounded(true);
		}
	}

	if (player.GetPosition().y > DISPLAY_HEIGHT)
	{
		player.SetDead(true);
	}
}