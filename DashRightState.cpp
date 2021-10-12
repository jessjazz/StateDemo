#include "DashRightState.h"
#include "RunRightState.h"
#include "Player.h"

constexpr float MAX_DASH = 10.0f;

PlayerState* DashRightState::HandleInput(Player& player)
{
	//player.SetDrawState(State::STATE_DASH_RIGHT);
	m_dashTime++;

	if (m_dashTime > MAX_DASH)
	{
		player.SetDrawState(State::STATE_RUN_RIGHT);
		return new RunRightState;
	}

	return nullptr;
}

void DashRightState::StateUpdate(Player& player)
{
	int speed = player.GetSpeed();

	player.SetPosition({ player.GetPosition().x + (speed * 2), player.GetPosition().y });
}
