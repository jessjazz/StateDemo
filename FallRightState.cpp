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

void FallRightState::StateUpdate(Player& player, GameObject* p_gameObject)
{
	Point2f oldPos = player.GetPosition();
	Point2f currentPos = oldPos;

	player.SetVelocity({ player.GetVelocity().x, player.GetVelocity().y + player.GetGravity() });
	player.SetPosition(currentPos + player.GetVelocity());

	if (player.IsColliding(player, p_gameObject) || player.GetPosition().y <= p_gameObject->GetHeight() - player.GetHeight())
	{
		player.SetGrounded(true);
	}
}
