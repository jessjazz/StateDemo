#pragma once
#include "PlayerState.h"

class Player;

class FallRightState : public PlayerState
{
public:
	FallRightState() {}

	PlayerState* HandleInput(Player& player) override;
	void StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const override;
	void Enter(Player& player) const override;
};

class FallLeftState : public PlayerState
{
public:
	FallLeftState() {}

	PlayerState* HandleInput(Player& player) override;
	void StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const override;
	void Enter(Player& player) const override;
};