#pragma once
#include "PlayerState.h"

class Player;

class CrawlState : public PlayerState
{
public:
	CrawlState(int direction)
		: m_direction(direction)
	{}

	PlayerState* HandleInput(Player& player) override;
	void StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const override;
	void Enter(Player& player) const override;

private:
	int m_direction;
};

