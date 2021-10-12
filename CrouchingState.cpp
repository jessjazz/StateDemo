#include "CrouchingState.h"
#include "IdleState.h"
#include "Player.h"

PlayerState* CrouchingState::HandleInput(Player& player)
{
	if (!Play::KeyDown(VK_DOWN))
	{
		player.SetDrawState(State::STATE_IDLE);
		return new IdleState;
	}
	return nullptr;
}

void CrouchingState::StateUpdate(Player& player)
{
}
