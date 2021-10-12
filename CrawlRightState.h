#pragma once
#include "PlayerState.h"

class Player;

class CrawlRightState : public PlayerState
{
public:
	CrawlRightState() {}

	PlayerState* HandleInput(Player& player) override;
	void StateUpdate(Player& player);
};

