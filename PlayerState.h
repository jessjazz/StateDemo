#pragma once
#include "Play.h"
#include "Coin.h"
#include "Gem.h"
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
	virtual void StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const = 0;

	void HandleCollision(Player& player, const std::vector<GameObject*>& map, 
						const int speed, const int direction) const;

	void HandleCoinPickup(Player& player, GameState& gState) const;
	void HandleGemPickup(Player& player, GameState& gState) const;
};

