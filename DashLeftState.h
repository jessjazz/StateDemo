#pragma once
#include "PlayerState.h"

class Player;

class DashLeftState : public PlayerState
{
public:
	DashLeftState() 
		: m_dashTime(0.0f)
	{}

	PlayerState* HandleInput(Player& player) override;
	void StateUpdate(Player& player, GameObject* p_gameObject) override;

private:
	float m_dashTime;
};
