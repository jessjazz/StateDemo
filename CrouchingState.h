#pragma once
#include "PlayerState.h"

class Player;

class CrouchingState : public PlayerState
{
public:
	CrouchingState() {}

	PlayerState* HandleInput(Player& player) override;
	void StateUpdate(Player& player);
};

