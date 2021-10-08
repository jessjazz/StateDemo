#include "CrouchingState.h"
#include "Player.h"

void CrouchingState::StateUpdate(Player& player)
{
	PlayBuffer& buff = PlayBuffer::Instance();

	if (!buff.KeyDown(VK_DOWN))
	{
		player.SetState(State::STATE_IDLE);
	}
}

void CrouchingState::HandleInput(Player& player)
{
}
