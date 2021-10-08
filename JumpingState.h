#pragma once
#include "PlayerState.h"

class Player;

class JumpingState : public PlayerState
{
public:
	JumpingState() {}

	void StateUpdate(Player& player) override;
	void HandleInput(Player& player) override;
};

