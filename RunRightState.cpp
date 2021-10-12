#include "DashRightState.h"
#include "IdleState.h"
#include "RunRightState.h"
#include "Player.h"

PlayerState* RunRightState::HandleInput(Player& player)
{
	if (!Play::KeyDown(VK_RIGHT))
	{
		player.SetDrawState(State::STATE_IDLE);
		return new IdleState;
	}

	if (Play::KeyDown(VK_RIGHT) && Play::KeyPressed(VK_SHIFT))
	{
		player.SetDrawState(State::STATE_DASH_RIGHT);
		return new DashRightState();
	}

	return nullptr;
}

void RunRightState::StateUpdate(Player& player)
{
	int speed = player.GetSpeed();

	player.SetPosition({ player.GetPosition().x + speed, player.GetPosition().y });
}
