#pragma once
#include "Play.h"
#include "Platform.h"
#include "MainGame.h"
#include "GameObject.h"

constexpr int RIGHT = 1;
constexpr int LEFT = -1;

class Player;

class PlayerState
{
public:
	PlayerState() {}
	virtual ~PlayerState() {}
	virtual PlayerState* HandleInput(Player& player) = 0;
	virtual void StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const = 0;

	void HandleCollision(Player& player, const std::vector<GameObject*>& map, 
						const int speed, const int direction) const;
};

