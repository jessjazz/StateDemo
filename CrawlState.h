#pragma once
#include "PlayerState.h"

class Player;

class CrawlRightState : public PlayerState
{
public:
	CrawlRightState() {}

	PlayerState* HandleInput(Player& player) override;
	void StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const;

	void HandleCollision(Player& player, const std::vector<GameObject*>& map,
		const int speed, const int direction) const;

	int DetectCollision(GameObject* object1, GameObject* object2) const;
};

class CrawlLeftState : public PlayerState
{
public:
	CrawlLeftState() {}

	PlayerState* HandleInput(Player& player) override;
	void StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const;

	void HandleCollision(Player& player, const std::vector<GameObject*>& map,
		const int speed, const int direction) const;

	int DetectCollision(GameObject* object1, GameObject* object2) const;
};

