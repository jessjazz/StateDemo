#pragma once
#include "PlayerState.h"

class Player;

class RunRightState : public PlayerState
{
public:
	RunRightState() {}

	PlayerState* HandleInput(Player& player) override;
	void StateUpdate(Player& player, GameObject* p_gameObject) override;
};

