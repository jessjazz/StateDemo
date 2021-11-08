#include "Star.h"

Star::Star(Point2f pos)
	: GameObject(pos)
{
	SetPosition(pos);
	SetType(OBJ_STAR);
	SetDrawOrder(5);
}

void Star::Update(GameState& gState)
{
	m_rot += m_rotationSpeed;
	m_velocity += m_accelaration;
	m_pos += m_velocity;

	if (GetPosition().y > LEVEL_HEIGHT || GetPosition().y < 0 || GetPosition().x > LEVEL_WIDTH || GetPosition().x < 0)
	{
		SetActive(false);
	}
}

void Star::Draw(GameState& gState) const
{
	Play::DrawSpriteRotated(gState.sprites.star, { m_pos.x - gState.camera.x, m_pos.y - gState.camera.y }, 1, m_rot, 0.5f);
}

void Star::SpawnStars(Point2f pos)
{
	for (float rad{ 0.25f }; rad < 2.0f; rad += 0.5f)
	{
		Star* newStar = new Star(pos);
		newStar->m_rotationSpeed = 0.1f;
		newStar->m_accelaration = { 0.0f, 0.5f };
		newStar->m_velocity.x = 16 * cos(rad * PLAY_PI);
		newStar->m_velocity.y = 16 * sin(rad * PLAY_PI);
	}
}
