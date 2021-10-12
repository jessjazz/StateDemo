#pragma once
#include "Play.h"
#include "PlayerState.h"

class Player;

class IdleLeftState : public PlayerState
{
public:
	IdleLeftState() {}

	PlayerState* HandleInput(Player& player) override;
	void StateUpdate(Player& player);
};

