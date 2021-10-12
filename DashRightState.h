#pragma once
#include "PlayerState.h"

class Player;

class DashRightState : public PlayerState
{
public:
	DashRightState() 
		: m_dashTime(0.0f)
	{}

	PlayerState* HandleInput(Player& player) override;
	void StateUpdate(Player& player) override;

private:
	float m_dashTime;
};

