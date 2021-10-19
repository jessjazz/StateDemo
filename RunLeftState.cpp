#include "SlideLeftState.h"
#include "DashLeftState.h"
#include "IdleLeftState.h"
#include "JumpLeftState.h"
#include "RunLeftState.h"
#include "Player.h"

constexpr int JUMP_HEIGHT = 650;

PlayerState* RunLeftState::HandleInput(Player& player)
{
	if (!Play::KeyDown(VK_LEFT))
	{
		player.SetDrawState(State::STATE_IDLE_LEFT);
		return new IdleLeftState;
	}

	if (Play::KeyPressed(VK_SHIFT))
	{
		player.SetDrawState(State::STATE_DASH_LEFT);
		return new DashLeftState;
	}

	if (Play::KeyPressed(VK_DOWN))
	{
		player.SetDrawState(State::STATE_SLIDE_LEFT);
		return new SlideLeftState;
	}

	if (Play::KeyPressed(VK_SPACE))
	{
		player.SetDrawState(State::STATE_JUMP_LEFT);
		return new JumpLeftState;
	}

	return nullptr;
}

void RunLeftState::StateUpdate(Player& player, GameObject* p_gameObject)
{
	Point2f oldPos = player.GetPosition();
	Point2f currentPos = oldPos;

	int spriteId = Play::GetSpriteId("run_left_8");
	player.SetHeight(Play::GetSpriteHeight(spriteId));
	player.SetWidth(Play::GetSpriteWidth(spriteId));

	int speed = player.GetSpeed();

	if (player.IsColliding(player, p_gameObject))
	{
		if (player.GetPosition().y <= DISPLAY_HEIGHT - p_gameObject->GetHeight())
		{
			player.SetVelocity({ -speed, 0 });
			player.SetPosition({ currentPos.x + player.GetVelocity().x, (p_gameObject->GetPosition().y - player.GetHeight() + 1) });
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
