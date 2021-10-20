#include "CrouchLeftState.h"
#include "CrawlRightState.h"
#include "CrawlLeftState.h"
#include "IdleLeftState.h"
#include "Player.h"

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
