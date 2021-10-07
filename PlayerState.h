#pragma once
#include "Play.h"
#include "Player.h"
#include "MainGame.h"
#include "GameObject.h"

class IdleState;
class JumpingState;

class PlayerState
{
public:
	PlayerState() {}
	virtual ~PlayerState() {}
	virtual void update(Player& player) = 0;
};

