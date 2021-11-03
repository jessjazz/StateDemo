#pragma once
#include "PlayerState.h"

class GroundPoundRightState : public PlayerState
{
public:
	GroundPoundRightState() {}

	PlayerState* HandleInput(Player& player) override;
	void StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const override;
	void Enter(Player& player) const override;

	void HandleCollision(Player& player, const std::vector<GameObject*>& map) const;

private:
	float m_smashTime{ 0.f };
};

class GroundPoundLeftState : public PlayerState
{
public:
	GroundPoundLeftState() {}

	PlayerState* HandleInput(Player& player) override;
	void StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const override;
	void Enter(Player& player) const override;

	void HandleCollision(Player& player, const std::vector<GameObject*>& map) const;

private:
	float m_smashTime{ 0.f };
};

