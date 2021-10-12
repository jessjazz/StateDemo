#include "SlideLeftState.h"
#include "DashLeftState.h"
#include "IdleLeftState.h"
#include "JumpLeftState.h"
#include "RunLeftState.h"
#include "Player.h"

constexpr int DISPLAY_HEIGHT = 720;

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

void RunLeftState::StateUpdate(Player& player)
{
	Point2f currentPos = player.GetPosition();

	if (player.GetPosition().y <= 650)
	{
		player.SetPosition({ currentPos.x, DISPLAY_HEIGHT - 90 });
	}

	int speed = player.GetSpeed();

	player.SetPosition({ player.GetPosition().x - speed, player.GetPosition().y });
}
