#include "CrawlState.h"
#include "CrouchingState.h"
#include "FallState.h"
#include "RunningState.h"
#include "Player.h"

PlayerState* CrawlState::HandleInput(Player& player)
{
	switch (m_direction)
	{
	case RIGHT:
		if (!Play::KeyDown(VK_RIGHT))
		{
			return new CrouchState(RIGHT);
		}

		if (!Play::KeyDown(VK_DOWN))
		{
			// Don't stop crouching if the player is beneath a low platform
			if (HandleCrouchingCollision(player) == UP)
			{
				return new RunState(RIGHT);
			}
		}

		if (!player.IsGrounded())
		{
			return new FallState(RIGHT);
		}

		return nullptr;
		break;

	case LEFT:
		if (!Play::KeyDown(VK_LEFT))
		{
			return new CrouchState(LEFT);
		}

		if (!Play::KeyDown(VK_DOWN))
		{
			// Don't stop crouching if the player is beneath a low platform
			if (HandleCrouchingCollision(player) == UP)
			{
				return new RunState(LEFT);
			}
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

void CrawlState::StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const
{
	int spriteId;
	Point2f currentPos = player.GetPosition();
	int speed = player.GetSpeed() / 2;

	switch (m_direction)
	{
	case RIGHT:
		// Set sprite dimensions
		spriteId = gState.sprites.crawlRight;
		player.SetHeight(Play::GetSpriteHeight(spriteId));
		player.SetWidth(Play::GetSpriteWidth(spriteId));
		HandleCollision(player, map, speed, RIGHT);
		break;
		
	case LEFT:
		// Set sprite dimensions
		spriteId = gState.sprites.crawlLeft;
		player.SetHeight(Play::GetSpriteHeight(spriteId));
		player.SetWidth(Play::GetSpriteWidth(spriteId));
		HandleCollision(player, map, speed, LEFT);
		break;
	}

	HandleCoinPickup(player, gState);
	HandleGemPickup(player, gState);
}

void CrawlState::Enter(Player& player) const
{
	switch (m_direction)
	{
	case RIGHT:
		player.SetDrawState(State::STATE_CRAWL_RIGHT);
		break;
	case LEFT:
		player.SetDrawState(State::STATE_CRAWL_LEFT);
		break;
	}
	player.SetCrouching(true);
}