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
		return new RunRightState;
	}
	else if (Play::KeyDown(VK_LEFT))
	{
		return new RunLeftState;
	}
	else if (Play::KeyPressed(VK_SPACE))
	{
		return new JumpRightState;
	}
	else if (Play::KeyPressed(VK_DOWN))
	{
		return new CrouchRightState;
	}
	else if (Play::KeyPressed(VK_CONTROL))
	{
		return new GroundPoundRightState;
	}
	
	if (!player.IsGrounded())
	{
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

void IdleRightState::Enter(Player& player) const
{
	player.SetDrawState(State::STATE_IDLE);
	player.SetCrouching(false);
}

PlayerState* IdleLeftState::HandleInput(Player& player)
{
	if (Play::KeyDown(VK_RIGHT))
	{
		return new RunRightState;
	}
	else if (Play::KeyDown(VK_LEFT))
	{
		return new RunLeftState;
	}
	else if (Play::KeyPressed(VK_SPACE))
	{
		return new JumpLeftState;
	}
	else if (Play::KeyPressed(VK_DOWN))
	{
		return new CrouchLeftState;
	}
	else if (Play::KeyPressed(VK_CONTROL))
	{
		return new GroundPoundLeftState;
	}

	if (!player.IsGrounded())
	{
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

void IdleLeftState::Enter(Player& player) const
{
	player.SetDrawState(State::STATE_IDLE_LEFT);
	player.SetCrouching(false);
}
