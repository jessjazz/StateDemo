#pragma once
#include "PlayerState.h"

class GroundPoundState : public PlayerState
{
public:
	GroundPoundState(int direction)
		: m_direction(direction)
	{}
	// Change states based on used input or certain player conditions
	PlayerState* HandleInput(Player& player) override;
	// Update position, handle collision and pickups
	void StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const override;
	// Set sprite and any state specific data
	void Enter(Player& player) const override;
	// Handle collision in a way specific to ground pound state, handles the destruction of platforms
	void HandleCollision(Player& player, const std::vector<GameObject*>& map) const;

protected:
	int m_direction;
	float m_smashTime{ 0.f }; // Records how long player has been in the state
};