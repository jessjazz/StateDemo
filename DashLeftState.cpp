#include "DashLeftState.h"
#include "RunLeftState.h"
#include "Player.h"

constexpr float MAX_DASH = 10.0f;

PlayerState* DashLeftState::HandleInput(Player& player)
{
	player.SetDrawState(State::STATE_DASH_LEFT);
	m_dashTime++;

	if (m_dashTime > MAX_DASH)
	{
		player.SetDrawState(State::STATE_RUN_LEFT);
		return new RunLeftState;
	}

	return nullptr;
}

void DashLeftState::StateUpdate(Player& player)
{
	int speed = player.GetSpeed();

	player.SetPosition({ player.GetPosition().x - (speed * 2), player.GetPosition().y });
}
