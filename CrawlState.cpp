#include "CrawlState.h"
#include "CrouchingState.h"
#include "FallState.h"
#include "RunningState.h"
#include "Player.h"

PlayerState* CrawlRightState::HandleInput(Player& player)
{
	if (!Play::KeyDown(VK_RIGHT))
	{
		return new CrouchRightState;
	}

	if (!Play::KeyDown(VK_DOWN))
	{
		return new RunRightState;
	}

	if (!player.IsGrounded())
	{
		return new FallRightState;
	}

	return nullptr;
}

void CrawlRightState::StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const
{
	// Set sprite dimensions
	int spriteId = gState.sprites.crawlRight;
	player.SetHeight(Play::GetSpriteHeight(spriteId));
	player.SetWidth(Play::GetSpriteWidth(spriteId));

	int speed = player.GetSpeed() / 2;

	HandleCollision(player, map, speed, RIGHT);
	HandleCoinPickup(player, gState);
	HandleGemPickup(player, gState);
}

void CrawlRightState::Enter(Player& player) const
{
	player.SetDrawState(State::STATE_CRAWL_RIGHT);
	player.SetCrouching(true);
}

PlayerState* CrawlLeftState::HandleInput(Player& player)
{
	if (!Play::KeyDown(VK_LEFT))
	{
		return new CrouchLeftState;
	}

	if (!Play::KeyDown(VK_DOWN))
	{
		return new RunLeftState;
	}

	if (!player.IsGrounded())
	{
		return new FallLeftState;
	}

	return nullptr;
}

void CrawlLeftState::StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const
{
	// Set sprite dimensions
	int spriteId = gState.sprites.crawlLeft;
	player.SetHeight(Play::GetSpriteHeight(spriteId));
	player.SetWidth(Play::GetSpriteWidth(spriteId));

	int speed = player.GetSpeed() / 2;

	HandleCollision(player, map, speed, LEFT);
	HandleCoinPickup(player, gState);
	HandleGemPickup(player, gState);
}

void CrawlLeftState::Enter(Player& player) const
{
	player.SetDrawState(State::STATE_CRAWL_LEFT);
	player.SetCrouching(true);
}
