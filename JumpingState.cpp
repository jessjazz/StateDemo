#include "IdleState.h"
#include "JumpingState.h"
#include "Player.h"
#include "RunRightState.h"
#include "RunLeftState.h"

constexpr int DISPLAY_HEIGHT = 720;
constexpr float MAX_JUMP = 10.0f;

PlayerState* JumpingState::HandleInput(Player& player)
{
	m_jumpTime++;
	
	if (!Play::KeyDown(VK_SPACE))
	{
		player.SetDrawState(State::STATE_IDLE);
		return new IdleState;
	}

	if (m_jumpTime > MAX_JUMP)
	{
		if (Play::KeyDown(VK_RIGHT))
		{
			player.SetDrawState(State::STATE_RUN_RIGHT);
			return new RunRightState;
		}
		//else if (Play::KeyDown(VK_LEFT))
		//{
		//	player.SetDrawState(State::STATE_RUN_LEFT);
		//	return new RunLeftState;
		//}
		else
		{
			player.SetDrawState(State::STATE_IDLE);
			return new IdleState;
		}
	}

	return nullptr;
}

void JumpingState::StateUpdate(Player& player)
{
	Point2f currentPos = player.GetPosition();

	if (player.GetPosition().y >= 600)
	{
		player.SetPosition({ player.GetPosition().x, player.GetPosition().y - 50 });
	}

	if (Play::KeyDown(VK_RIGHT))
	{
		player.SetPosition({ player.GetPosition().x + 12, player.GetPosition().y });
	}

	//if (Play::KeyDown(VK_LEFT))
	//{
	//	player.SetPosition({ player.GetPosition().x - 12, player.GetPosition().y });
	//}
}
