#pragma once
#include "PlayerState.h"

class Player;

class JumpingState : public PlayerState
{
public:
	JumpingState() 
		: m_jumpTime(0.0f)
	{}

	PlayerState* HandleInput(Player& player) override;
	void StateUpdate(Player& player, GameObject* p_gameObject) override;

private:
	float m_jumpTime;
};

