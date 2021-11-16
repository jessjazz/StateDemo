#pragma once
#include "PlayerState.h"

class Player;

class FallState : public PlayerState
{
public:
	FallState(int direction)
		: m_direction(direction)
	{}
	// Change states based on used input or certain player conditions
	PlayerState* HandleInput(Player& player) override;
	// Update position, handle collision, pickups and death
	void StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const override;
	// Set sprite and any state specific data
	void Enter(Player& player) const override;
	// Handle collision in a way specific to fall state
	void HandleCollision(Player& player, const std::vector<GameObject*>& map) const;

protected:
	int m_direction;
};