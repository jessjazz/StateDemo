#include "CrouchingState.h"
#include "FallState.h"
#include "GroundPoundState.h"
#include "IdleState.h"
#include "JumpingState.h"
#include "Player.h"
#include "RunningState.h"

PlayerState* IdleState::HandleInput(Player& player)
{
	switch (m_direction)
	{
	case RIGHT:
		if (Play::KeyDown(VK_RIGHT))
		{
			return new RunState(RIGHT);
		}
		else if (Play::KeyDown(VK_LEFT))
		{
			return new RunState(LEFT);
		}
		else if (Play::KeyPressed(VK_SPACE))
		{
			return new JumpState(RIGHT);
		}
		else if (Play::KeyPressed(VK_DOWN))
		{
			return new CrouchState(RIGHT);
		}
		else if (Play::KeyPressed(VK_CONTROL))
		{
			return new GroundPoundState(RIGHT);
		}
	
		if (!player.IsGrounded())
		{
			return new FallState(RIGHT);
		}
		return nullptr;
		break;

	case LEFT:
		if (Play::KeyDown(VK_RIGHT))
		{
			return new RunState(RIGHT);
		}
		else if (Play::KeyDown(VK_LEFT))
		{
			return new RunState(LEFT);
		}
		else if (Play::KeyPressed(VK_SPACE))
		{
			return new JumpState(LEFT);
		}
		else if (Play::KeyPressed(VK_DOWN))
		{
			return new CrouchState(LEFT);
		}
		else if (Play::KeyPressed(VK_CONTROL))
		{
			return new GroundPoundState(LEFT);
		}

		if (!player.IsGrounded())
		{
			return new FallState(LEFT);
		}
		return nullptr;
		break;

	default:
		return nullptr;
		break;
	}
}

void IdleState::StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const
{
	int spriteId;
	
	switch (m_direction)
	{
	case RIGHT:
		// Set sprite dimensions
		spriteId = gState.sprites.idleRight;
		player.SetHeight(Play::GetSpriteHeight(spriteId));
		player.SetWidth(Play::GetSpriteWidth(spriteId));
		break;
	case LEFT:
		// Set sprite dimensions
		spriteId = gState.sprites.idleLeft;
		player.SetHeight(Play::GetSpriteHeight(spriteId));
		player.SetWidth(Play::GetSpriteWidth(spriteId));
		break;
	}

	HandleCollision(player, map);
}

void IdleState::Enter(Player& player) const
{
	switch (m_direction)
	{
	case RIGHT:
		player.SetDrawState(State::STATE_IDLE);
		break;
	case LEFT:
		player.SetDrawState(State::STATE_IDLE_LEFT);
		break;
	}

	player.SetCrouching(false);
}

void IdleState::HandleCollision(Player& player, const std::vector<GameObject*>& map) const
{
	Point2f currentPos = player.GetPosition();
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