#pragma once
#include "PlayerState.h"

class SlideRightState : public PlayerState
{
public:
	SlideRightState()
		: m_slideTime(0.0f)
	{}

	PlayerState* HandleInput(Player& player) override;
	void StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const override;

private:
	float m_slideTime;
};

class SlideLeftState : public PlayerState
{
public:
	SlideLeftState()
		: m_slideTime(0.0f)
	{}

	PlayerState* HandleInput(Player& player) override;
	void StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const override;

private:
	float m_slideTime;
};