#include "DashRightState.h"
#include "Player.h"

void DashRightState::StateUpdate(Player& player)
{
	if (!Play::KeyDown(VK_SHIFT))
	{
		player.SetState(State::STATE_RUN_RIGHT);
	}
}

void DashRightState::HandleInput(Player& player)
{
	int speed = player.GetSpeed();

	if (Play::KeyDown(VK_RIGHT) && Play::KeyDown(VK_SHIFT))
	{
		player.SetPosition({ player.GetPosition().x + (speed * 2), player.GetPosition().y });
	}
}
