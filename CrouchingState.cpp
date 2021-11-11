#include "CrouchingState.h"
#include "CrawlState.h"
#include "IdleState.h"
#include "Player.h"

CrouchState::CrouchState(int direction)
	: m_direction(direction)
{}

PlayerState* CrouchState::HandleInput(Player& player)
{
	switch (m_direction)
	{
	case RIGHT:
		if (!Play::KeyDown(VK_DOWN))
		{
			if (HandleCrouchingCollision(player) == 0)
			{
				return new IdleRightState;
			}
		}

		if (Play::KeyDown(VK_RIGHT))
		{
			return new CrawlRightState;
		}

		if (Play::KeyDown(VK_LEFT))
		{
			return new CrawlLeftState;
		}
		return nullptr;
		break;

	case LEFT:
		if (!Play::KeyDown(VK_DOWN))
		{
			if (HandleCrouchingCollision(player) == 0)
			{
				return new IdleLeftState;
			}
		}

		if (Play::KeyDown(VK_RIGHT))
		{
			return new CrawlRightState;
		}

		if (Play::KeyDown(VK_LEFT))
		{
			return new CrawlLeftState;
		}
		return nullptr;
		break;

	default:
		return nullptr;
		break;
	}
}

void CrouchState::StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const
{
	int spriteId;
	Point2f currentPos;

	switch (m_direction)
	{
	case RIGHT:
		// Set sprite dimensions
		spriteId = gState.sprites.crouchRight;
		player.SetHeight(Play::GetSpriteHeight(spriteId));
		player.SetWidth(Play::GetSpriteWidth(spriteId));

		currentPos = player.GetPosition();

		for (GameObject* p : map)
		{
			if (IsStandingOn(&player, p))
			{
				player.SetPosition({ currentPos.x + p->GetVelocity().x, p->GetPosition().y - player.GetHeight() });
				player.SetGrounded(true);
			}
		}
		break;

	case LEFT:
		// Set sprite dimensions
		spriteId = gState.sprites.crouchLeft;
		player.SetHeight(Play::GetSpriteHeight(spriteId));
		player.SetWidth(Play::GetSpriteWidth(spriteId));

		currentPos = player.GetPosition();

		for (GameObject* p : map)
		{
			if (IsStandingOn(&player, p))
			{
				player.SetPosition({ currentPos.x + p->GetVelocity().x, p->GetPosition().y - player.GetHeight() });
				player.SetGrounded(true);
			}
		}
		break;

	default:
		break;
	}
}

void CrouchState::Enter(Player& player) const
{
	switch (m_direction)
	{
	case RIGHT:
		player.SetDrawState(State::STATE_CROUCH);
		player.SetCrouching(true);
		break;

	case LEFT:
		player.SetDrawState(State::STATE_CROUCH_LEFT);
		player.SetCrouching(true);
		break;

	default:
		break;
	}
}

