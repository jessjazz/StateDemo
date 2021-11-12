#include "DecayingPlatform.h"
#include "Player.h"

float DecayingPlatform::deathTime;

DecayingPlatform::DecayingPlatform(Point2f pos, int width, int height, int decaySpeed, char size, float lifeTime, float respawnDelay)
	: Platform(pos, width, height),
	m_decaySpeed(decaySpeed),
	m_lifeTime(lifeTime),
	m_respawnDelay(respawnDelay)
{
	SetPosition(pos);
	SetType(OBJ_DECAYING_PLATFORM);
	SetDrawOrder(2);
	SetHeight(height);
	SetWidth(width);
	if (size == 'L' || size == 'l')
	{
		SetSize(LARGE);
	}
	else if (size == 'S' || size == 's')
	{
		SetSize(SMALL);
	}
}

void DecayingPlatform::Update(GameState& gState)
{
	std::vector<GameObject*> players;
	GetObjectList(GameObject::Type::OBJ_PLAYER, players);
	for (GameObject* p : players)
	{
		Player* player = static_cast<Player*>(p);
		// Reduce remaining life while player is standing on platform, use remaining life to control alpha/fade platform
		if (IsStandingOn(player, this))
		{
			m_remainingLife -= gState.deltaTime * m_decaySpeed;
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
				// Delay respawning the platform so the player can fall through it
				if (gState.time > deathTime + m_respawnDelay)
				{
					ResetPlatform();
				}
			}
		}
		else
		{
			if (gState.time > deathTime + m_respawnDelay || player->IsDead())
			{
				ResetPlatform();
			}
		}
	}
}

void DecayingPlatform::Draw(GameState& gState) const
{
	if (!b_isInvisible)
	{
		switch (m_size)
		{
		case SMALL:
			Play::DrawSpriteTransparent(gState.sprites.smallPlatform, { m_pos.x - gState.camera.x, m_pos.y - gState.camera.y }, 1, m_alpha);
			break;
		case LARGE:
			Play::DrawSpriteTransparent(gState.sprites.largePlatform, { m_pos.x - gState.camera.x, m_pos.y - gState.camera.y }, 1, m_alpha);
		}
	}
}

DecayingPlatform* DecayingPlatform::CreatePlatform(Point2f pos, int width, int height, int decaySpeed, char size, float lifeTime, float respawnDelay)
{
	return new DecayingPlatform(pos, width, height, decaySpeed, size, lifeTime, respawnDelay);
}

void DecayingPlatform::ResetPlatform()
{
	m_alpha = m_originalAlpha;
	m_remainingLife = m_lifeTime;
	b_isInvisible = false;
	b_collidable = true;
}
