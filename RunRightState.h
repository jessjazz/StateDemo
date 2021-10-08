#pragma once
#include "PlayerState.h"

class Player;

class RunRightState : public PlayerState
{
public:
	RunRightState() {}

	void StateUpdate(Player& player) override;
	void HandleInput(Player& player) override;
};

