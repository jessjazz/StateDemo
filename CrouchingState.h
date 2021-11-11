#pragma once
#include "PlayerState.h"

class Player;

class CrouchState : public PlayerState
{
public:
	CrouchState(int direction);

	PlayerState* HandleInput(Player& player) override;
	void StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const override;
	void Enter(Player& player) const override;

private:
	int m_currentPos{ 0 };
	int m_direction{ 0 };
};

