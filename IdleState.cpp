#include "IdleState.h"
#include "Player.h"
#include "JumpingState.h"
#include "CrouchingState.h"
#include "RunLeftState.h"
#include "RunRightState.h"

constexpr int DISPLAY_HEIGHT = 720;

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

void IdleState::StateUpdate(Player& player)
{
	Point2f currentPos = player.GetPosition();

	if (player.GetPosition().y <= 650)
	{
		player.SetPosition({ currentPos.x, DISPLAY_HEIGHT - 90 });
	}
}
