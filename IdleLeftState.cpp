#include "IdleLeftState.h"
#include "Player.h"
#include "JumpLeftState.h"
#include "CrouchLeftState.h"
#include "RunLeftState.h"
#include "RunRightState.h"

PlayerState* IdleLeftState::HandleInput(Player& player)
{
	if (Play::KeyDown(VK_RIGHT))
	{
		player.SetDrawState(State::STATE_RUN_RIGHT);
		return new RunRightState;
	}
	else if (Play::KeyDown(VK_LEFT))
	{
		player.SetDrawState(State::STATE_RUN_LEFT);
		return new RunLeftState;
	}
	else if (Play::KeyPressed(VK_SPACE))
	{
		player.SetDrawState(State::STATE_JUMP_LEFT);
		return new JumpLeftState;
	}
	else if (Play::KeyPressed(VK_DOWN))
	{
		player.SetDrawState(State::STATE_CROUCH_LEFT);
		return new CrouchLeftState;
	}
    return nullptr;
}

void IdleLeftState::StateUpdate(Player& player, GameObject* p_gameObject)
{
	Point2f oldPos = player.GetPosition();
	Point2f currentPos = oldPos;

	int spriteId = Play::GetSpriteId("idle_left_7");
	player.SetHeight(Play::GetSpriteHeight(spriteId));
	player.SetWidth(Play::GetSpriteWidth(spriteId));

	if (player.GetPosition().y > DISPLAY_HEIGHT - player.GetHeight() && !player.IsColliding(player, p_gameObject))
	{
		player.SetVelocity({ 0, 0 });
		player.SetPosition({ currentPos.x, DISPLAY_HEIGHT - player.GetHeight() });
		player.SetGrounded(true);
	}

	if (player.IsColliding(player, p_gameObject) && !player.IsGrounded())
	{
		player.SetPosition({ currentPos.x, p_gameObject->GetPosition().y - player.GetHeight() });
		player.SetVelocity({ 0,0 });
		player.SetGrounded(true);
	}
	else if (!player.IsColliding(player, p_gameObject) && !player.IsGrounded())
	{
		player.SetVelocity({ player.GetVelocity().x, player.GetVelocity().y + player.GetGravity() });
		player.SetPosition(currentPos + player.GetVelocity());
	}
}
