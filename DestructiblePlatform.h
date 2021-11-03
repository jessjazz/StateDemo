#pragma once
#include "Platform.h"
class DestructiblePlatform : public Platform
{
public:
	DestructiblePlatform(Point2f pos, int width, int height, float lifeTime, float fadeSpeed);
	~DestructiblePlatform() {}

	void Update(GameState& gState) override;
	void Draw(GameState& gState) const override;

	static DestructiblePlatform* CreatePlatform(Point2f pos, int width, int height, float lifeTime, float fadeSpeed);

	enum State
	{
		STATE_APPEAR = 0,
		STATE_BROKEN
	};

	void SetState(State newState) { m_state = newState; }
	State GetState() const { return m_state; }

private:
	State m_state{ STATE_APPEAR };
	int m_frameIndex{ 0 };
	float m_lifeTime;
	float m_remainingLife{ m_lifeTime };
	float m_life{ 0.f };
	float m_fadeSpeed;
	float m_originalAlpha{ 1.f };
	float m_alpha{ m_originalAlpha };
};

