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
	// Control player state based on keyboard/mouse input
	virtual PlayerState* HandleInput(Player& player) = 0;
	// Updates player's position, handle collisions and pickups
	virtual void StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const = 0;
	// Enter the player state, set the sprite and any state specific data
	virtual void Enter(Player& player) const = 0;
	// Set the player's position when colliding with any platforms
	void HandleCollision(Player& player, const std::vector<GameObject*>& map, 
						const int speed, const int direction) const;
	// Returns any number other than 0 if player in crouching/crawling/sliding state collides with a platform above
	int HandleCrouchingCollision(Player& player);
	// Checks for collision with coin, adds to coin count and spawns stars
	void HandleCoinPickup(Player& player, GameState& gState) const;
	// Checks for collision with gem, adds to lives count and spawns stars
	void HandleGemPickup(Player& player, GameState& gState) const;
	// Plays a random scream for use in fallState
	void PlayFallScream() const;

protected:
	// Count used in crouching collision check
	int hitCount{ 0 };
};

