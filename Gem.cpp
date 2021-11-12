#include "Gem.h"

Gem::Gem(Point2f pos)
	: GameObject(pos)
{
	SetPosition(pos);
	SetType(OBJ_GEM);
	SetDrawOrder(2);
	SetVelocity({ 5.f, -8.f });
	SetHeight(24);
	SetWidth(23);
}

void Gem::Update(GameState& gState)
{
	// Move in an arc until gem lands on a platform
	if (!b_onGround)
	{
		m_velocity += GRAVITY;
	}

	for (GameObject* p : s_vUpdateList)
	{
		if (p->GetType() == OBJ_PLATFORM)
		{
			if (IsStandingOn(this, p))
			{
				b_onGround = true;
				m_velocity = { 0,0 };
				m_pos.y = p->GetPosition().y - m_height;
			}
		}
	}
	
	m_pos += m_velocity;
}

void Gem::Draw(GameState& gState) const
{
	if (b_collidable)
	{
		Play::DrawSprite(gState.sprites.gem, { m_pos.x - gState.camera.x, m_pos.y - gState.camera.y }, 1);
	}
}

Gem* Gem::SpawnGem(Point2f pos)
{
	return new Gem(pos);
}
