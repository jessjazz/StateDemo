#pragma once
#include "Platform.h"

class MovingPlatform : public Platform
{
public:
	MovingPlatform(Point2f pos, int width, int height, int direction, float sinAmplitude, float sinFrequency);
	~MovingPlatform() {}

	void Update(GameState& gState) override;
	void Draw(GameState& gState) const override;
	// Create function to hide raw new
	static MovingPlatform* CreatePlatform(Point2f pos, int width, int height, int direction, float sinAmplitude, float sinFrequency);

protected:
	float x { 0.f }; // Time counter for sine wave
	float m_amplitude; // Change this to control how far the platform moves
	float m_frequency; // Change this to control how fast the platform moves
	float m_xoffset{ 0.0f }; // Change this to adjust where the platform moves from on x axis
	float m_yoffset{ 0.0f }; // Change this to adjust where the platform moves from on y axis
	int m_direction;
};

