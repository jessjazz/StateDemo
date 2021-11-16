#pragma once
#include "Platform.h"

class DecayingPlatform : public Platform
{
public:
	// Size controls which sprite to use
	enum Size
	{
		SMALL = 0,
		LARGE,
	};

	DecayingPlatform(Point2f pos, int width, int height, int decaySpeed, char size, float lifeTime, float respawnDelay);
	~DecayingPlatform() {}

	void Update(GameState& gState) override;
	void Draw(GameState& gState) const override;
	// Create function to hide raw new
	static DecayingPlatform* CreatePlatform(Point2f pos, int width, int height, int decaySpeed, char size, float lifeTime, float respawnDelay);

	void SetSize(Size size) { m_size = size; }

protected:
	Size m_size;
	float m_lifeTime;
	float m_remainingLife{ m_lifeTime };
	float m_life{ 0.0f };
	int m_decaySpeed;
	float m_originalAlpha{ 1.0f }; // Fully opaque to start with = 1.0f
	float m_alpha{ m_originalAlpha };
	bool b_isInvisible{ false };
	float m_respawnDelay;
	static float deathTime;
	// Reset remainingLife, alpha and collision
	void ResetPlatform();
};

