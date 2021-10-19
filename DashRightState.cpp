#include "DashRightState.h"
#include "FallRightState.h"
#include "RunRightState.h"
#include "Player.h"

constexpr float MAX_DASH = 10.0f;

PlayerState* DashRightState::HandleInput(Player& player)
{
	m_dashTime++;

	if (m_dashTime > MAX_DASH)
	{
		player.SetDrawState(State::STATE_RUN_RIGHT);
		return new RunRightState;
	}

	if (!player.IsGrounded())
	{
		player.SetDrawState(State::STATE_FALL_RIGHT);
		return new FallRightState;
	}

	return nullptr;
}

void DashRightState::StateUpdate(Player& player, GameObject* p_gameObject)
{
	Point2f oldPos = player.GetPosition();
	Point2f currentPos = oldPos;

	int spriteId = Play::GetSpriteId("dash_right_4");
	player.SetHeight(Play::GetSpriteHeight(spriteId));
	player.SetWidth(Play::GetSpriteWidth(spriteId));

	int speed = player.GetSpeed();
	player.SetVelocity({ speed * 2, 0 });
	Vector2f velocity = player.GetVelocity();

	if (player.IsColliding(player, p_gameObject))
	{
		if (player.GetPosition().y <= DISPLAY_HEIGHT - p_gameObject->GetHeight())
		{
			player.SetPosition(currentPos + velocity);
		}
		else
		{
			player.SetPosition(oldPos);
		}
	}
	else
	{
		player.SetVelocity({ 0, 0 + player.GetGravity() });
		player.SetPosition(currentPos + player.GetVelocity());
		player.SetGrounded(false);
	}
}
