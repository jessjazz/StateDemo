#pragma once
#include "GameObject.h"
class Gem : public GameObject
{
public:
	Gem(Point2f pos);
	~Gem() {}

	void Update(GameState& gState);
	void Draw(GameState& gState) const;
	// Create function to hide raw new
	static Gem* SpawnGem(Point2f pos);

private:
	bool b_onGround{ false }; // To stop gems falling through platforms
};

