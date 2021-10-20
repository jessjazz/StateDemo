#pragma once
#include "PlayerState.h"

class SlideLeftState : public PlayerState
{
public:
	SlideLeftState()
		: m_slideTime(0.0f)
	{}

	PlayerState* HandleInput(Player& player) override;
	void StateUpdate(Player& player, std::vector<GameObject*> map) override;

private:
	float m_slideTime;
};

