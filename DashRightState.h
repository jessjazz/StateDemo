#pragma once
#include "PlayerState.h"

class Player;

class DashRightState : public PlayerState
{
public:
	DashRightState() {}

	void StateUpdate(Player& player) override;
	void HandleInput(Player& player) override;
};

