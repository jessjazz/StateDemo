#pragma once
#include "PlayerState.h"

class Player;

class DashRightState : public PlayerState
{
public:
	DashRightState() {}

	PlayerState* HandleInput(Player& player) override;
	void StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const override;
	void Enter(Player& player) const override;

private:
	float m_dashTime{ 0.0f };
};

class DashLeftState : public PlayerState
{
public:
	DashLeftState() {}

	PlayerState* HandleInput(Player& player) override;
	void StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const override;
	void Enter(Player& player) const override;

private:
	float m_dashTime{ 0.0f };
};