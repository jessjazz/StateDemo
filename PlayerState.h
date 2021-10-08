#pragma once
#include "Play.h"
#include "MainGame.h"
#include "GameObject.h"

class Player;

class PlayerState
{
public:
	PlayerState() {}
	virtual ~PlayerState() {}
	virtual void StateUpdate(Player& player) = 0;
	virtual void HandleInput(Player& player) = 0;
};

