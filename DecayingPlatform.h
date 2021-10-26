#pragma once
#include "Platform.h"
class DecayingPlatform : public Platform
{
public:
	DecayingPlatform(Point2f pos, int width, int height);
	~DecayingPlatform() {}

	void Update(GameState& gState) override;
	void Draw(GameState& gState) const override;

private:
	float m_lifeTime;
	float m_remainingLife = m_lifeTime;
	float m_life;
	float m_originalAlpha;
	float m_alpha{ m_originalAlpha };
	bool b_isInvisible;
	float m_respawnDelay;
	static float deathTime;
};

