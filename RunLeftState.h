#pragma once
#include "PlayerState.h"

class Player;

class RunLeftState : public PlayerState
{
public:
	RunLeftState() {}

	PlayerState* HandleInput(Player& player) override;
	void StateUpdate(Player& player, GameObject* p_gameObject) override;
};

