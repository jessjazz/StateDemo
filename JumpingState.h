#pragma once
#include "PlayerState.h"

class Player;

class JumpRightState : public PlayerState
{
public:
	JumpRightState() 
		: m_jumpTime(0.0f)
	{}

	PlayerState* HandleInput(Player& player) override;
	void StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const override;

private:
	float m_jumpTime;
};

class JumpLeftState : public PlayerState
{
public:
	JumpLeftState()
		: m_jumpTime(0.0f)
	{}

	PlayerState* HandleInput(Player& player) override;
	void StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const override;

private:
	float m_jumpTime;
};