#include "FallLeftState.h"
#include "Player.h"
#include "RunLeftState.h"

PlayerState* FallLeftState::HandleInput(Player& player)
{
	if (player.IsGrounded())
	{
		player.SetDrawState(State::STATE_RUN_LEFT);
		return new RunLeftState;
	}
	return nullptr;
}

void FallLeftState::StateUpdate(Player& player, GameObject* p_gameObject)
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
