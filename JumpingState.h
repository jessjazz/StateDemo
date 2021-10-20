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
	void StateUpdate(Player& player, std::vector<GameObject*> map) override;

private:
	float m_jumpTime;
};

