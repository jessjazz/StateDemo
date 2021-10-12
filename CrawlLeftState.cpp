#include "CrawlLeftState.h"
#include "CrouchLeftState.h"
#include "RunLeftState.h"
#include "Player.h"

PlayerState* CrawlLeftState::HandleInput(Player& player)
{
	if (!Play::KeyDown(VK_LEFT))
	{
		player.SetDrawState(State::STATE_CROUCH_LEFT);
		return new CrouchLeftState;
	}

	if (!Play::KeyDown(VK_DOWN))
	{
		player.SetDrawState(State::STATE_RUN_LEFT);
		return new RunLeftState;
	}

	return nullptr;
}

void CrawlLeftState::StateUpdate(Player& player)
{
	int speed = player.GetSpeed() / 2;

	player.SetPosition({ player.GetPosition().x - speed, player.GetPosition().y });
}
