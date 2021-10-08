#pragma once
#include "Play.h"
#include "PlayerState.h"

class Player;

class IdleState : public PlayerState
{
public:
	IdleState() {}

	void StateUpdate(Player& player) override;
	void HandleInput(Player& player);
};

