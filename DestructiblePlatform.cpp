#include "DestructiblePlatform.h"
#include "Gem.h"

DestructiblePlatform::DestructiblePlatform(Point2f pos, int width, int height, float lifeTime, float fadeSpeed)
	: Platform(pos, width, height),
	m_lifeTime(lifeTime),
	m_fadeSpeed(fadeSpeed)
{
	SetPosition(pos);
	SetWidth(width);
	SetHeight(height);
	SetType(OBJ_DESTRUCTIBLE_PLATFORM);
}

void DestructiblePlatform::Update(GameState& gState)
{
	// Reset platform after lifeTime has ended if game has been reset (after game over or level end)
	if (m_state == STATE_APPEAR && m_remainingLife <= 0)
	{
		m_remainingLife = m_lifeTime;
		b_visible = true;
		b_collidable = true;
	}
	// Fade away broken pieces and spawn a gem
	if (m_state == STATE_BROKEN)
	{
		b_collidable = false;
		m_remainingLife -= gState.deltaTime * m_fadeSpeed;
		m_life = m_remainingLife / m_lifeTime;
		m_alpha = m_originalAlpha * m_life;

		if (m_remainingLife <= 0.0f && b_visible)
		{
			Gem* gem = Gem::SpawnGem({ m_pos.x + (GetWidth() / 2) - 20, m_pos.y });
			gState.s_vPickups.push_back(gem);
			b_visible = false;
			b_collidable = false;
		}
	}
}

void DestructiblePlatform::Draw(GameState& gState) const
{
	// Draw whole platform or broken pieces slightly apart from each other to show the platform has been smashed
	if (b_visible)
	{
		switch (m_state)
		{
		case STATE_APPEAR:
			Play::DrawSprite(gState.sprites.detructiblePlatform, { m_pos.x - gState.camera.x, m_pos.y - gState.camera.y }, 0);
			break;
		case STATE_BROKEN:
			Play::DrawSpriteTransparent(gState.sprites.brokenPlatform, { m_pos.x - 15 - gState.camera.x, m_pos.y - gState.camera.y }, 0, m_alpha);
			Play::DrawSpriteTransparent(gState.sprites.brokenPlatform, { m_pos.x - gState.camera.x, m_pos.y - 10 - gState.camera.y }, 1, m_alpha);
			Play::DrawSpriteTransparent(gState.sprites.brokenPlatform, { m_pos.x + 15 - gState.camera.x, m_pos.y - gState.camera.y }, 2, m_alpha);
			break;
		default:
			break;
		}
	}
}

DestructiblePlatform* DestructiblePlatform::CreatePlatform(Point2f pos, int width, int height, float lifeTime, float fadeSpeed)
{
	return new DestructiblePlatform(pos, width, height, lifeTime, fadeSpeed);
}
