#include "JumpingState.h"
#include "Player.h"

void JumpingState::StateUpdate(Player& player)
{
	if (!Play::KeyDown(VK_SPACE))
	{
		player.SetState(State::STATE_IDLE);
	}
}

void JumpingState::HandleInput(Player& player)
{
	Point2f currentPos = player.GetPosition();

	if (Play::KeyPressed(VK_SPACE))
	{
		player.SetPosition({ player.GetPosition().x, player.GetPosition().y - 50 }); //this line doesn't actually move the player up
	}
	else
	{
		player.SetPosition(currentPos);
	}
}
