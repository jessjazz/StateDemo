#pragma once
#include "Play.h"
#include "PlayerState.h"

class IdleState : public PlayerState
{
public:
	IdleState() {}
	~IdleState() {}

	void update(Player& player) override;
};

