#pragma once
#include "PlayerState.h"

class Player;

class FallRightState : public PlayerState
{
public:
	FallRightState() {}

	PlayerState* HandleInput(Player& player) override;
	void StateUpdate(Player& player, GameObject* p_gameObject) override;
};

