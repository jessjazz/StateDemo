#pragma once
#include "PlayerState.h"

class Player;

class CrouchRightState : public PlayerState
{
public:
	CrouchRightState() {}

	PlayerState* HandleInput(Player& player) override;
	void StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const;
};

class CrouchLeftState : public PlayerState
{
public:
	CrouchLeftState() {}

	PlayerState* HandleInput(Player& player) override;
	void StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const;
};

