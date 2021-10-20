#include "FallRightState.h"
#include "Player.h"
#include "RunRightState.h"

PlayerState* FallRightState::HandleInput(Player& player)
{
	if (player.IsGrounded())
	{
		player.SetDrawState(State::STATE_RUN_RIGHT);
		return new RunRightState;
	}
	return nullptr;
}

void FallRightState::StateUpdate(Player& player, std::vector<GameObject*> map)
{
	Point2f oldPos = player.GetPosition();
	Point2f currentPos = oldPos;

	player.SetVelocity({ player.GetVelocity().x, player.GetVelocity().y + player.GetGravity() });
	player.SetPosition(currentPos + player.GetVelocity());

	for (GameObject* p : map)
	{
		if (player.IsColliding(player, p))
		{
			player.SetGrounded(true);
		}
	}

	if (player.GetPosition().y > DISPLAY_HEIGHT)
	{
		player.SetDead(true);
	}
}
