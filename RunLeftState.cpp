#include "RunLeftState.h"
#include "Player.h"

void RunLeftState::StateUpdate(Player& player)
{
	if (!Play::KeyDown(VK_LEFT))
	{
		player.SetState(State::STATE_IDLE);
	}
}

void RunLeftState::HandleInput(Player& player)
{
	// Point2f currentPos = player.GetPosition();
	int speed = player.GetSpeed();

	if (Play::KeyDown(VK_LEFT))
	{
		player.SetPosition({ player.GetPosition().x - speed, player.GetPosition().y });
	}
}
