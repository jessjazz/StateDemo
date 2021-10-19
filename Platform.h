#pragma once
#include "GameObject.h"
class Platform : public GameObject
{
public:
	Platform(Point2f pos);
	~Platform() {}

	void Update(GameState& gState) override;
	void Draw(GameState& gState) const override;
};

