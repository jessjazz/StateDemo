#pragma once
#include "PlayerState.h"

class Player;

class RunState : public PlayerState
{
public:
	RunState(int direction)
		: m_direction(direction)
	{}
	// Change states based on used input or certain player conditions
	PlayerState* HandleInput(Player& player) override;
	// Update position, handle collision and pickups
	void StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const override;
	// Set sprite and any state specific data
	void Enter(Player& player) const override;

private:
	int m_direction;
};