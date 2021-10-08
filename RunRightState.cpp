#include "RunRightState.h"
#include "Player.h"

void RunRightState::StateUpdate(Player& player)
{
	if (!Play::KeyDown(VK_RIGHT))
	{
		player.SetState(State::STATE_IDLE);
	}

	if (Play::KeyDown(VK_RIGHT) && Play::KeyPressed(VK_SHIFT))
	{
		player.SetState(State::STATE_DASH_RIGHT);
	}
}

void RunRightState::HandleInput(Player& player)
{
	int speed = player.GetSpeed();

	if (Play::KeyDown(VK_RIGHT))
	{
		player.SetPosition({ player.GetPosition().x + speed, player.GetPosition().y });
	}
}
