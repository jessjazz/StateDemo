#pragma once
#include "Play.h"
#include "PlayerState.h"
#include "MainGame.h"
#include "GameObject.h"

class Player : public GameObject
{
public:
	Player(Point2f pos);
	~Player();

	void Update(GameState& gState) override;
	void Draw(GameState& gState) const override;
};
