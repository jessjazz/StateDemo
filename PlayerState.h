#pragma once
#include "Play.h"
#include "Platform.h"
#include "MainGame.h"
#include "GameObject.h"

class Player;

class PlayerState
{
public:
	PlayerState() {}
	virtual ~PlayerState() {}
	virtual PlayerState* HandleInput(Player& player) = 0;
	virtual void StateUpdate(Player& player, std::vector<GameObject*> map) = 0;
};

