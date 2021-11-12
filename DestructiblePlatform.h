#pragma once
#include "Platform.h"
class DestructiblePlatform : public Platform
{
public:
	DestructiblePlatform(Point2f pos, int width, int height, float lifeTime, float fadeSpeed);
	~DestructiblePlatform() {}

	void Update(GameState& gState) override;
	void Draw(GameState& gState) const override;
	// Create function to hide raw new
	static DestructiblePlatform* CreatePlatform(Point2f pos, int width, int height, float lifeTime, float fadeSpeed);
	// Enum of states to control sprites and platform behaviour
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
	float m_life{ 0.0f };
	float m_fadeSpeed;
	float m_originalAlpha{ 1.0f }; // Fully opaque to start with = 1.0f
	float m_alpha{ m_originalAlpha };
	bool b_visible{ true };
};

