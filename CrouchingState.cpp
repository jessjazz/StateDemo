#include "CrouchingState.h"
#include "CrawlRightState.h"
#include "CrawlLeftState.h"
#include "IdleState.h"
#include "Player.h"

PlayerState* CrouchingState::HandleInput(Player& player)
{
	if (!Play::KeyDown(VK_DOWN))
	{
		player.SetDrawState(State::STATE_IDLE);
		return new IdleState;
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

void CrouchingState::StateUpdate(Player& player)
{
}
