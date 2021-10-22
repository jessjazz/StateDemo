#include "IdleState.h"
#include "Player.h"
#include "JumpingState.h"
#include "CrouchingState.h"
#include "RunningState.h"

PlayerState* IdleRightState::HandleInput(Player& player)
{
	if (Play::KeyDown(VK_RIGHT))
	{
		player.SetDrawState(State::STATE_RUN_RIGHT);
		return new RunRightState;
	}
	else if (Play::KeyDown(VK_LEFT))
	{
		player.SetDrawState(State::STATE_RUN_LEFT);
		return new RunLeftState;
	}
	else if (Play::KeyPressed(VK_SPACE))
	{
		player.SetDrawState(State::STATE_JUMP);
		return new JumpRightState;
	}
	else if (Play::KeyPressed(VK_DOWN))
	{
		player.SetDrawState(State::STATE_CROUCH);
		return new CrouchRightState;
	}
	return nullptr;
}

void IdleRightState::StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const
{
	Point2f currentPos = player.GetPosition();;

	int spriteId = gState.sprites.idleRight;
	player.SetHeight(Play::GetSpriteHeight(spriteId));
	player.SetWidth(Play::GetSpriteWidth(spriteId));

	for (GameObject* p : map)
	{
		if (player.IsStandingOn(&player, p))
		{
			player.SetPosition({ currentPos.x, p->GetPosition().y - player.GetHeight() });
			player.SetVelocity({ 0,0 });
			player.SetGrounded(true);
		}
	}
}

PlayerState* IdleLeftState::HandleInput(Player& player)
{
	if (Play::KeyDown(VK_RIGHT))
	{
		player.SetDrawState(State::STATE_RUN_RIGHT);
		return new RunRightState;
	}
	else if (Play::KeyDown(VK_LEFT))
	{
		player.SetDrawState(State::STATE_RUN_LEFT);
		return new RunLeftState;
	}
	else if (Play::KeyPressed(VK_SPACE))
	{
		player.SetDrawState(State::STATE_JUMP_LEFT);
		return new JumpLeftState;
	}
	else if (Play::KeyPressed(VK_DOWN))
	{
		player.SetDrawState(State::STATE_CROUCH_LEFT);
		return new CrouchLeftState;
	}
	return nullptr;
}

void IdleLeftState::StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const
{
	Point2f currentPos = player.GetPosition();;

	int spriteId = gState.sprites.idleLeft;
	player.SetHeight(Play::GetSpriteHeight(spriteId));
	player.SetWidth(Play::GetSpriteWidth(spriteId));

	for (GameObject* p : map)
	{
		if (player.IsStandingOn(&player, p))
		{
			player.SetPosition({ currentPos.x, p->GetPosition().y - player.GetHeight() });
			player.SetVelocity({ 0,0 });
			player.SetGrounded(true);
		}
	}
}