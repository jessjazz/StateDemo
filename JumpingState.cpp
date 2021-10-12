#include "IdleState.h"
#include "JumpingState.h"
#include "Player.h"

constexpr int DISPLAY_HEIGHT = 720;

PlayerState* JumpingState::HandleInput(Player& player)
{
	if (!Play::KeyDown(VK_SPACE))
	{
		player.SetDrawState(State::STATE_IDLE);
		return new IdleState;
	}
	return nullptr;
}

void JumpingState::StateUpdate(Player& player)
{
	Point2f currentPos = player.GetPosition();

	if (player.GetPosition().y >= 600)
	{
		player.SetPosition({ player.GetPosition().x, player.GetPosition().y - 50 });
	}
}
