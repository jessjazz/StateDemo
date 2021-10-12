#pragma once
#include "PlayerState.h"

class Player;

class CrouchLeftState : public PlayerState
{
public:
	CrouchLeftState() {}

	PlayerState* HandleInput(Player& player) override;
	void StateUpdate(Player& player);
};
