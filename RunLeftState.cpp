#include "RunLeftState.h"
#include "Player.h"

void RunLeftState::StateUpdate(Player& player)
{
	PlayBuffer& buff = PlayBuffer::Instance();

	if (!buff.KeyDown(VK_LEFT))
	{
		player.SetState(State::STATE_IDLE);
	}
}

void RunLeftState::HandleInput(Player& player)
{
	PlayBuffer& buff = PlayBuffer::Instance();

	// Point2f currentPos = player.GetPosition();
	int speed = player.GetSpeed();

	if (buff.KeyDown(VK_LEFT))
	{
		player.SetPosition({ player.GetPosition().x - speed, player.GetPosition().y });
	}
}
