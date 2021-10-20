#pragma once
#include "Play.h"
#include "PlayerState.h"

class Player;

class IdleRightState : public PlayerState
{
public:
	IdleRightState() {}

	PlayerState* HandleInput(Player& player) override;
	void StateUpdate(Player& player, std::vector<GameObject*> map);
};

class IdleLeftState : public PlayerState
{
public:
	IdleLeftState() {}

	PlayerState* HandleInput(Player& player) override;
	void StateUpdate(Player& player, std::vector<GameObject*> map);
};