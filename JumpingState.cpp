#include "JumpingState.h"
#include "Player.h"

void JumpingState::StateUpdate(Player& player)
{
	PlayBuffer& buff = PlayBuffer::Instance();

	if (!buff.KeyDown(VK_SPACE))
	{
		player.SetState(State::STATE_IDLE);
	}
}

void JumpingState::HandleInput(Player& player)
{
	PlayBuffer& buff = PlayBuffer::Instance();

	Point2f currentPos = player.GetPosition();

	if (buff.KeyPressed(VK_SPACE))
	{
		player.SetPosition({ player.GetPosition().x, player.GetPosition().y - 50 }); //this line doesn't actually move the player up
	}
	else
	{
		player.SetPosition(currentPos);
	}
}
