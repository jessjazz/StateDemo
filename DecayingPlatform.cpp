#include "DecayingPlatform.h"

float DecayingPlatform::deathTime;

DecayingPlatform::DecayingPlatform(Point2f pos, int width, int height)
	: Platform(pos, width, height),
	m_lifeTime(10.f),
	m_originalAlpha(1.f),
	m_life(0.f),
	b_isInvisible(false),
	m_respawnDelay(2.0f)
{
	SetPosition(pos);
	SetType(OBJ_DECAYING_PLATFORM);
	SetDrawOrder(2);
	SetHeight(height);
	SetWidth(width);
}

void DecayingPlatform::Update(GameState& gState)
{
	m_remainingLife -= gState.deltaTime * 4;
	m_life = m_remainingLife / m_lifeTime;
	m_alpha = m_originalAlpha * m_life;

	if (m_remainingLife <= 0.0f)
	{
		b_isInvisible = true;
		b_collidable = false;
		if (m_remainingLife > -0.05f)
		{
			deathTime = gState.time;
		}
	}

	if (b_isInvisible)
	{
		if (gState.time > deathTime + m_respawnDelay)
		{
			m_alpha = m_originalAlpha;
			m_remainingLife = m_lifeTime;
			b_isInvisible = false;
			b_collidable = true;
		}
	}
}

void DecayingPlatform::Draw(GameState& gState) const
{
	if (!b_isInvisible)
	{
		Play::DrawSpriteTransparent(gState.sprites.platform, { m_pos.x - gState.camera.x, m_pos.y - gState.camera.y }, 1, m_alpha);
	}
}
