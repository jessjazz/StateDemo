#pragma once
#include "Play.h"
#include "PlayerState.h"

class Player;

class IdleState : public PlayerState
{
public:
	IdleState(int direction)
		: m_direction(direction)
	{}

	PlayerState* HandleInput(Player& player) override;
	void StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const override;
	void Enter(Player& player) const override;

	void HandleCollision(Player& player, const std::vector<GameObject*>& map) const;

private:
	int m_direction;
};