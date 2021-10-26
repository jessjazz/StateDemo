#pragma once
#include "Platform.h"

class MovingPlatform : public Platform
{
public:
	MovingPlatform(Point2f pos, int width, int height, int direction);
	~MovingPlatform() {}

	void Update(GameState& gState) override;
	void Draw(GameState& gState) const override;

private:
	float x { 0.f };
	float m_amplitude;
	float m_frequency;
	float m_xoffset;
	float m_yoffset;
	float m_direction;
};

