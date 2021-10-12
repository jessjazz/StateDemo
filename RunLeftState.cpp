#include "DashLeftState.h"
#include "IdleState.h"
#include "RunLeftState.h"
#include "Player.h"

PlayerState* RunLeftState::HandleInput(Player& player)
{
	if (!Play::KeyDown(VK_LEFT))
	{
		player.SetDrawState(State::STATE_IDLE);
		return new IdleState;
	}

	if (Play::KeyDown(VK_LEFT) && Play::KeyPressed(VK_SHIFT))
	{
		player.SetDrawState(State::STATE_DASH_LEFT);
		return new DashLeftState();
	}
	return nullptr;
}

void RunLeftState::StateUpdate(Player& player)
{
	int speed = player.GetSpeed();

	player.SetPosition({ player.GetPosition().x - speed, player.GetPosition().y });
}
