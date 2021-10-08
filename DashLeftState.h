#pragma once
#include "PlayerState.h"

class Player;

class DashLeftState : public PlayerState
{
public:
	DashLeftState() {}

	void StateUpdate(Player& player) override;
	void HandleInput(Player& player) override;
};
