#pragma once
#include "PlayerState.h"

class Player;

class DashState : public PlayerState
{
public:
	DashState(int direction)
		: m_direction(direction)
	{}

	PlayerState* HandleInput(Player& player) override;
	void StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const override;
	void Enter(Player& player) const override;

private:
	int m_direction;
	float m_dashTime{ 0.0f };
};