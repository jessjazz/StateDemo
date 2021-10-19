#pragma once
#include "PlayerState.h"

class Player;

class CrawlLeftState : public PlayerState
{
public:
	CrawlLeftState() {}

	PlayerState* HandleInput(Player& player) override;
	void StateUpdate(Player& player, GameObject* p_gameObject);
};

