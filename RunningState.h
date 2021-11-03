#pragma once
#include "PlayerState.h"

class Player;

class RunRightState : public PlayerState
{
public:
	RunRightState() {}

	PlayerState* HandleInput(Player& player) override;
	void StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const override;
	void Enter(Player& player) const override;
};

class RunLeftState : public PlayerState
{
public:
	RunLeftState() {}

	PlayerState* HandleInput(Player& player) override;
	void StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const override;
	void Enter(Player& player) const override;
};