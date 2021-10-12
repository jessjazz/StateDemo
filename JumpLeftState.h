#pragma once
#include "PlayerState.h"

class Player;

class JumpLeftState : public PlayerState
{
public:
	JumpLeftState()
		: m_jumpTime(0.0f)
	{}

	PlayerState* HandleInput(Player& player) override;
	void StateUpdate(Player& player) override;

private:
	float m_jumpTime;
};

