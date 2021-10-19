#include "DashLeftState.h"
#include "FallLeftState.h"
#include "RunLeftState.h"
#include "Player.h"

constexpr float MAX_DASH = 10.0f;

PlayerState* DashLeftState::HandleInput(Player& player)
{
	m_dashTime++;

	if (m_dashTime > MAX_DASH)
	{
		player.SetDrawState(State::STATE_RUN_LEFT);
		return new RunLeftState;
	}

	if (!player.IsGrounded())
	{
		player.SetDrawState(State::STATE_FALL_LEFT);
		return new FallLeftState;
	}

	return nullptr;
}

void DashLeftState::StateUpdate(Player& player, GameObject* p_gameObject)
{
	Point2f oldPos = player.GetPosition();
	Point2f currentPos = oldPos;

	int spriteId = Play::GetSpriteId("dash_left_4");
	player.SetHeight(Play::GetSpriteHeight(spriteId));
	player.SetWidth(Play::GetSpriteWidth(spriteId));

	int speed = player.GetSpeed();
	player.SetVelocity({ speed * 2, 0 });
	Vector2f velocity = player.GetVelocity();

	if (player.IsColliding(player, p_gameObject))
	{
		if (player.GetPosition().y <= DISPLAY_HEIGHT - p_gameObject->GetHeight())
		{
			player.SetPosition(currentPos - velocity);
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
