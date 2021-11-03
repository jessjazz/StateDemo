#pragma once
#include "Platform.h"

class MovingPlatform : public Platform
{
public:
	MovingPlatform(Point2f pos, int width, int height, int direction, float sinAmplitude, float sinFrequency);
	~MovingPlatform() {}

	void Update(GameState& gState) override;
	void Draw(GameState& gState) const override;

	static MovingPlatform* CreatePlatform(Point2f pos, int width, int height, int direction, float sinAmplitude, float sinFrequency);

private:
	float x { 0.f };
	float m_amplitude;
	float m_frequency;
	float m_xoffset{ 0 };
	float m_yoffset{ 0 };
	int m_direction;
};

