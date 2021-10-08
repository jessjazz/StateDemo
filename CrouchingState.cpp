#include "CrouchingState.h"
#include "Player.h"

void CrouchingState::StateUpdate(Player& player)
{
	if (!Play::KeyDown(VK_DOWN))
	{
		player.SetState(State::STATE_IDLE);
	}
}

void CrouchingState::HandleInput(Player& player)
{
}
