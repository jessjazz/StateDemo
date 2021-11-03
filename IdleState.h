#pragma once
#include "Play.h"
#include "PlayerState.h"

class Player;

class IdleRightState : public PlayerState
{
public:
	IdleRightState() {}

	PlayerState* HandleInput(Player& player) override;
	void StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const override;
	void Enter(Player& player) const override;
};

class IdleLeftState : public PlayerState
{
public:
	IdleLeftState() {}

	PlayerState* HandleInput(Player& player) override;
	void StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const override;
	void Enter(Player& player) const override;
};