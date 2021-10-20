#include "CrouchingState.h"
#include "CrawlState.h"
#include "IdleState.h"
#include "Player.h"

PlayerState* CrouchRightState::HandleInput(Player& player)
{
	if (!Play::KeyDown(VK_DOWN))
	{
		player.SetDrawState(State::STATE_IDLE);
		return new IdleRightState;
	}

	if (Play::KeyDown(VK_RIGHT))
	{
		player.SetDrawState(State::STATE_CRAWL_RIGHT);
		return new CrawlRightState;
	}

	if (Play::KeyDown(VK_LEFT))
	{
		player.SetDrawState(State::STATE_CRAWL_LEFT);
		return new CrawlLeftState;
	}
	return nullptr;
}

void CrouchRightState::StateUpdate(Player& player, std::vector<GameObject*> map)
{
	Point2f oldPos = player.GetPosition();
	Point2f currentPos = oldPos;

	int spriteId = Play::GetSpriteId("crouch_6");
	player.SetHeight(Play::GetSpriteHeight(spriteId));
	player.SetWidth(Play::GetSpriteWidth(spriteId));

	for (GameObject* p : map)
	{
		if (player.IsColliding(player, p))
		{
			player.SetPosition(oldPos);
			player.SetGrounded(true);
		}
	}
}

PlayerState* CrouchLeftState::HandleInput(Player& player)
{
	if (!Play::KeyDown(VK_DOWN))
	{
		player.SetDrawState(State::STATE_IDLE_LEFT);
		return new IdleLeftState;
	}

	if (Play::KeyDown(VK_RIGHT))
	{
		player.SetDrawState(State::STATE_CRAWL_RIGHT);
		return new CrawlRightState;
	}

	if (Play::KeyDown(VK_LEFT))
	{
		player.SetDrawState(State::STATE_CRAWL_LEFT);
		return new CrawlLeftState;
	}
	return nullptr;
}

void CrouchLeftState::StateUpdate(Player& player, std::vector<GameObject*> map)
{
	int spriteId = Play::GetSpriteId("crouch_left_6");
	player.SetHeight(Play::GetSpriteHeight(spriteId));
	player.SetWidth(Play::GetSpriteWidth(spriteId));

	Point2f oldPos = player.GetPosition();
	Point2f currentPos = oldPos;

	for (GameObject* p : map)
	{
		if (player.IsColliding(player, p))
		{
			player.SetPosition(oldPos);
			player.SetGrounded(true);
		}
	}
}