#include "CrawlRightState.h"
#include "CrouchingState.h"
#include "RunRightState.h"
#include "Player.h"

PlayerState* CrawlRightState::HandleInput(Player& player)
{
	if (!Play::KeyDown(VK_RIGHT))
	{
		player.SetDrawState(State::STATE_CROUCH);
		return new CrouchingState;
	}

	if (!Play::KeyDown(VK_DOWN))
	{
		player.SetDrawState(State::STATE_RUN_RIGHT);
		return new RunRightState;
	}

	return nullptr;
}

void CrawlRightState::StateUpdate(Player& player)
{
	int speed = player.GetSpeed() / 2;

	player.SetPosition({ player.GetPosition().x + speed, player.GetPosition().y });
}
