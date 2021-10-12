#pragma once
#include "Play.h"
#include "PlayerState.h"

class Player;

class IdleState : public PlayerState
{
public:
	IdleState() {}

	PlayerState* HandleInput(Player& player) override;
	void StateUpdate(Player& player);
};

