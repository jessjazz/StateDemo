#include "CrouchingState.h"
#include "FallState.h"
#include "GroundPoundState.h"
#include "IdleState.h"
#include "JumpingState.h"
#include "Player.h"
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
	else if (Play::KeyPressed(VK_CONTROL))
	{
		player.SetDrawState(State::STATE_SMASH_RIGHT);
		player.SetFrame(0);
		player.SetAnimSpeed(0.25f);
		return new GroundPoundRightState;
	}
	
	if (!player.IsGrounded())
	{
		player.SetDrawState(State::STATE_FALL_RIGHT);
		return new FallRightState;
	}
	return nullptr;
}

void IdleRightState::StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const
{
	// Set sprite dimensions
	int spriteId = gState.sprites.idleRight;
	player.SetHeight(Play::GetSpriteHeight(spriteId));
	player.SetWidth(Play::GetSpriteWidth(spriteId));

	Point2f currentPos = player.GetPosition();;

	for (GameObject* p : map)
	{
		if (IsStandingOn(&player, p))
		{
			if (p->GetType() == GameObject::Type::OBJ_MOVING_PLATFORM)
			{
				player.SetPosition({ currentPos.x + p->GetVelocity().x, p->GetPosition().y - player.GetHeight() });
				player.SetGrounded(true);
			}
			else if (p->GetType() == GameObject::Type::OBJ_DECAYING_PLATFORM || p->GetType() == GameObject::Type::OBJ_DESTRUCTIBLE_PLATFORM)
			{
				if (p->IsCollidable())
				{
					player.SetPosition({ currentPos.x, p->GetPosition().y - player.GetHeight() });
					player.SetVelocity({ 0,0 });
					player.SetGrounded(true);
				}
				else
				{
					player.SetGrounded(false);
				}
			}
			else
			{
				player.SetPosition({ currentPos.x, p->GetPosition().y - player.GetHeight() });
				player.SetVelocity({ 0,0 });
				player.SetGrounded(true);
			}
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
	else if (Play::KeyPressed(VK_CONTROL))
	{
		player.SetDrawState(State::STATE_SMASH_LEFT);
		player.SetFrame(0);
		player.SetAnimSpeed(0.25f);
		return new GroundPoundLeftState;
	}

	if (!player.IsGrounded())
	{
		player.SetDrawState(State::STATE_FALL_LEFT);
		return new FallLeftState;
	}
	return nullptr;
}

void IdleLeftState::StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const
{
	// Set sprite dimensions
	int spriteId = gState.sprites.idleLeft;
	player.SetHeight(Play::GetSpriteHeight(spriteId));
	player.SetWidth(Play::GetSpriteWidth(spriteId));

	Point2f currentPos = player.GetPosition();;
	
	for (GameObject* p : map)
	{
		if (IsStandingOn(&player, p))
		{
			if (p->GetType() == GameObject::Type::OBJ_MOVING_PLATFORM)
			{
				player.SetPosition({ currentPos.x + p->GetVelocity().x, p->GetPosition().y - player.GetHeight() });
				player.SetGrounded(true);
			}
			else if (p->GetType() == GameObject::Type::OBJ_DECAYING_PLATFORM || p->GetType() == GameObject::Type::OBJ_DESTRUCTIBLE_PLATFORM)
			{
				if (p->IsCollidable())
				{
					player.SetPosition({ currentPos.x, p->GetPosition().y - player.GetHeight() });
					player.SetVelocity({ 0,0 });
					player.SetGrounded(true);
				}
				else
				{
					player.SetGrounded(false);
				}
			}
			else
			{
				player.SetPosition({ currentPos.x, p->GetPosition().y - player.GetHeight() });
				player.SetVelocity({ 0,0 });
				player.SetGrounded(true);
			}
		}
	}
}