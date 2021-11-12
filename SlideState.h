#pragma once
#include "PlayerState.h"

class SlideState : public PlayerState
{
public:
	SlideState(int direction)
		: m_direction(direction)
	{}

	PlayerState* HandleInput(Player& player) override;
	void StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const override;
	void Enter(Player& player) const override;

private:
	int m_direction;
	float m_slideTime{ 0.0f };
};