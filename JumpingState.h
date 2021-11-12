#pragma once
#include "PlayerState.h"

class Player;

class JumpState : public PlayerState
{
public:
	JumpState(int direction) 
		: m_jumpTime(0.0f), m_direction(direction)
	{}
	// Change states based on used input or certain player conditions
	PlayerState* HandleInput(Player& player) override;
	// Update position, handle collision and pickups
	void StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const override;
	// Set sprite and any state specific data
	void Enter(Player& player) const override;
	// Handle collision in a way specific to jumping state
	void HandleJumpCollision(Player& player, const std::vector<GameObject*>& map) const;

private:
	int m_direction;
	float m_jumpTime; // Amount of time the player has been in the air
};