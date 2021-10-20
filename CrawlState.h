#pragma once
#include "PlayerState.h"

class Player;

class CrawlRightState : public PlayerState
{
public:
	CrawlRightState() {}

	PlayerState* HandleInput(Player& player) override;
	void StateUpdate(Player& player, std::vector<GameObject*> map);
};

class CrawlLeftState : public PlayerState
{
public:
	CrawlLeftState() {}

	PlayerState* HandleInput(Player& player) override;
	void StateUpdate(Player& player, std::vector<GameObject*> map);
};

