#include "CrouchingState.h"
#include "CrawlState.h"
#include "IdleState.h"
#include "Player.h"

PlayerState* CrouchState::HandleInput(Player& player)
{
	switch (m_direction)
	{
	case RIGHT:
		if (!Play::KeyDown(VK_DOWN))
		{
			if (HandleCrouchingCollision(player) == 0)
			{
				return new IdleState(RIGHT);
			}
		}

		if (Play::KeyDown(VK_RIGHT))
		{
			return new CrawlState(RIGHT);
		}

		if (Play::KeyDown(VK_LEFT))
		{
			return new CrawlState(LEFT);
		}
		return nullptr;
		break;

	case LEFT:
		if (!Play::KeyDown(VK_DOWN))
		{
			if (HandleCrouchingCollision(player) == 0)
			{
				return new IdleState(LEFT);
			}
		}

		if (Play::KeyDown(VK_RIGHT))
		{
			return new CrawlState(RIGHT);
		}

		if (Play::KeyDown(VK_LEFT))
		{
			return new CrawlState(LEFT);
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
	Point2f currentPos = player.GetPosition();

	switch (m_direction)
	{
	case RIGHT:
		// Set sprite dimensions
		spriteId = gState.sprites.crouchRight;
		player.SetHeight(Play::GetSpriteHeight(spriteId));
		player.SetWidth(Play::GetSpriteWidth(spriteId));
		break;

	case LEFT:
		// Set sprite dimensions
		spriteId = gState.sprites.crouchLeft;
		player.SetHeight(Play::GetSpriteHeight(spriteId));
		player.SetWidth(Play::GetSpriteWidth(spriteId));
		break;
	}
	
	for (GameObject* p : map)
	{
		if (IsStandingOn(&player, p))
		{
			player.SetPosition({ currentPos.x + p->GetVelocity().x, p->GetPosition().y - player.GetHeight() });
			player.SetGrounded(true);
		}
	}
}

void CrouchState::Enter(Player& player) const
{
	switch (m_direction)
	{
	case RIGHT:
		player.SetDrawState(State::STATE_CROUCH);
		break;

	case LEFT:
		player.SetDrawState(State::STATE_CROUCH_LEFT);
		break;
	}
	player.SetCrouching(true);	// used in both states
}

