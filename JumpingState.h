#pragma once
#include "PlayerState.h"

class Player;

class JumpingState : public PlayerState
{
public:
	JumpingState() {}

	PlayerState* HandleInput(Player& player) override;
	void StateUpdate(Player& player) override;
};

