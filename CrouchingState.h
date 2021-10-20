#pragma once
#include "PlayerState.h"

class Player;

class CrouchRightState : public PlayerState
{
public:
	CrouchRightState() {}

	PlayerState* HandleInput(Player& player) override;
	void StateUpdate(Player& player, std::vector<GameObject*> map);
};

class CrouchLeftState : public PlayerState
{
public:
	CrouchLeftState() {}

	PlayerState* HandleInput(Player& player) override;
	void StateUpdate(Player& player, std::vector<GameObject*> map);
};

