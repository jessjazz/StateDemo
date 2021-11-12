#pragma once
#include "GameObject.h"

class Coin : public GameObject
{
public:
	Coin(Point2f pos);
	~Coin() {}

	void Update(GameState& gState);
	void Draw(GameState& gState) const;
	// Create function to hide raw new
	static Coin* CreateCoin(Point2f pos);

	static bool IsColliding(GameObject* object1, GameObject* object2, bool isCrouching);
};

