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
		int collisionDirection = player.DetectCollision(&player, p);
		if (collisionDirection == 2)
		{
			player.SetVelocity({ 0, player.GetVelocity().y });
		}
	}

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
		player.SetLives(player.GetLives() - 1);
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
		int collisionDirection = player.DetectCollision(&player, p);
		if (collisionDirection == -1)
		{
			player.SetVelocity({ 0, player.GetVelocity().y });
		}
	}

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