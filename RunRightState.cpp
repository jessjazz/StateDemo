#include "RunRightState.h"
#include "Player.h"

void RunRightState::StateUpdate(Player& player)
{

	if (!Play::KeyDown(VK_RIGHT))
	{
		player.SetState(State::STATE_IDLE);
	}
}

void RunRightState::HandleInput(Player& player)
{
	// Point2f currentPos = player.GetPosition();
	int speed = player.GetSpeed();

	if (Play::KeyDown(VK_RIGHT))
	{
		player.SetPosition({ player.GetPosition().x + speed, player.GetPosition().y });
	}
}
