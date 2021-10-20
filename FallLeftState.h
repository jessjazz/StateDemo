#pragma once
#include "PlayerState.h"

class Player;

class FallLeftState : public PlayerState
{
public:
	FallLeftState() {}
	
	PlayerState* HandleInput(Player& player) override;
	void StateUpdate(Player& player, std::vector<GameObject*> map) override;
};

