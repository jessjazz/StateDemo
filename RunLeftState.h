#pragma once
#include "PlayerState.h"

class Player;

class RunLeftState : public PlayerState
{
public:
	RunLeftState() {}

	void StateUpdate(Player& player) override;
	void HandleInput(Player& player) override;
};

