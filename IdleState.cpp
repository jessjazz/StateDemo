#include "IdleState.h"
#include "Player.h"

void IdleState::StateUpdate(Player& player)
{
	if (Play::KeyDown(VK_RIGHT))
	{
		player.SetState(State::STATE_RUN_RIGHT);
	}
	else if (Play::KeyDown(VK_LEFT))
	{
		player.SetState(State::STATE_RUN_LEFT);
	}
	else if (Play::KeyPressed(VK_SPACE))
	{
		player.SetState(State::STATE_JUMP);
	}
	else if (Play::KeyPressed(VK_DOWN))
	{
		player.SetState(State::STATE_CROUCH);
	}
}

void IdleState::HandleInput(Player& player)
{
}
