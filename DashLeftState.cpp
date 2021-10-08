#include "DashLeftState.h"
#include "Player.h"

void DashLeftState::StateUpdate(Player& player)
{
	if (!Play::KeyDown(VK_SHIFT))
	{
		player.SetState(State::STATE_RUN_LEFT);
	}
}

void DashLeftState::HandleInput(Player& player)
{
	int speed = player.GetSpeed();

	if (Play::KeyDown(VK_LEFT) && Play::KeyDown(VK_SHIFT))
	{
		player.SetPosition({ player.GetPosition().x - (speed * 2), player.GetPosition().y });
	}
}
