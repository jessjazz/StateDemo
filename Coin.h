#pragma once
#include "GameObject.h"

class Coin : public GameObject
{
public:
	Coin(Point2f pos);
	~Coin() {}

	void Update(GameState& gState);
	void Draw(GameState& gState) const;
};

