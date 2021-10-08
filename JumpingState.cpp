#include "JumpingState.h"
#include "Player.h"

constexpr int DISPLAY_HEIGHT = 720;

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

	if (Play::KeyDown(VK_SPACE) && player.GetPosition().y >= 600)
	{
		player.SetPosition({ player.GetPosition().x, player.GetPosition().y - 50 });
	}
	else if (!Play::KeyDown(VK_SPACE))
	{
		player.SetPosition({ currentPos.x, DISPLAY_HEIGHT - 90 });
	}

}
