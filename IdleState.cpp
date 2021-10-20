#include "IdleState.h"
#include "Player.h"
#include "JumpingState.h"
#include "CrouchingState.h"
#include "RunLeftState.h"
#include "RunRightState.h"

PlayerState* IdleState::HandleInput(Player& player)
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
		player.SetDrawState(State::STATE_JUMP);
		return new JumpingState;
	}
	else if (Play::KeyPressed(VK_DOWN))
	{
		player.SetDrawState(State::STATE_CROUCH);
		return new CrouchingState;
	}
	return nullptr;
}

void IdleState::StateUpdate(Player& player, std::vector<GameObject*> map)
{
	Point2f oldPos = player.GetPosition();
	Point2f currentPos = oldPos;

	int spriteId = Play::GetSpriteId("idle_7");
	player.SetHeight(Play::GetSpriteHeight(spriteId));
	player.SetWidth(Play::GetSpriteWidth(spriteId));

	for (GameObject* p : map)
	{
		if (player.IsColliding(player, p) && !player.IsGrounded())
		{
			player.SetPosition({ currentPos.x, p->GetPosition().y - player.GetHeight() });
			player.SetVelocity({ 0,0 });
			player.SetGrounded(true);
		}
	}
}
