#include "JumpLeftState.h"
#include "IdleLeftState.h"
#include "Player.h"
#include "RunRightState.h"
#include "RunLeftState.h"

constexpr int DISPLAY_HEIGHT = 720;
constexpr float MAX_JUMP = 10.0f;

PlayerState* JumpLeftState::HandleInput(Player& player)
{
	m_jumpTime++;

	if (!Play::KeyDown(VK_SPACE))
	{
		player.SetDrawState(State::STATE_IDLE_LEFT);
		return new IdleLeftState;
	}

	if (m_jumpTime > MAX_JUMP)
	{
		//if (Play::KeyDown(VK_RIGHT))
		//{
		//	player.SetDrawState(State::STATE_RUN_RIGHT);
		//	return new RunRightState;
		//}
		if (Play::KeyDown(VK_LEFT))
		{
			player.SetDrawState(State::STATE_RUN_LEFT);
			return new RunLeftState;
		}
		else
		{
			player.SetDrawState(State::STATE_IDLE_LEFT);
			return new IdleLeftState;
		}
	}

	return nullptr;
}

void JumpLeftState::StateUpdate(Player& player)
{
	Point2f currentPos = player.GetPosition();

	if (player.GetPosition().y >= 600)
	{
		player.SetPosition({ player.GetPosition().x, player.GetPosition().y - 50 });
	}

	if (Play::KeyDown(VK_LEFT))
	{
		player.SetPosition({ player.GetPosition().x - 12, player.GetPosition().y });
	}
}
