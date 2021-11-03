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
	void HandleCollision(Player& player, const std::vector<GameObject*>& map) const;
};

class FallLeftState : public PlayerState
{
public:
	FallLeftState() {}

	PlayerState* HandleInput(Player& player) override;
	void StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const override;
	void Enter(Player& player) const override;
	void HandleCollision(Player& player, const std::vector<GameObject*>& map) const;
};