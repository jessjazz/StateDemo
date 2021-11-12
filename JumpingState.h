#pragma once
#include "PlayerState.h"

class Player;

class JumpState : public PlayerState
{
public:
	JumpState(int direction) 
		: m_jumpTime(0.0f), m_direction(direction)
	{}

	PlayerState* HandleInput(Player& player) override;
	void StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const override;
	void Enter(Player& player) const override;

	void HandleJumpCollision(Player& player, const std::vector<GameObject*>& map) const;

private:
	int m_direction;
	float m_jumpTime;
};