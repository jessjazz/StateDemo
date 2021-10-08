#pragma once
#include "PlayerState.h"

class Player;

class CrouchingState : public PlayerState
{
public:
	CrouchingState() {}

	void StateUpdate(Player& player) override;
	void HandleInput(Player& player);
};

