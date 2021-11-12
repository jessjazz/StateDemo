#pragma once
#include "PlayerState.h"

class Player;

class FallState : public PlayerState
{
public:
	FallState(int direction)
		: m_direction(direction)
	{}

	PlayerState* HandleInput(Player& player) override;
	void StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const override;
	void Enter(Player& player) const override;
	void HandleCollision(Player& player, const std::vector<GameObject*>& map) const;

private:
	int m_direction;
};