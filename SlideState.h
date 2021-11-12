#pragma once
#include "PlayerState.h"

class SlideState : public PlayerState
{
public:
	SlideState(int direction)
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
	float m_slideTime{ 0.0f }; // Amount of time the player has been sliding
};