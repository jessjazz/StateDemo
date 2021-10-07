#pragma once
#include "PlayerState.h"
class JumpingState : public PlayerState
{
public:
	JumpingState() {}
	~JumpingState() {}

	void update(Player& player) override;
};

