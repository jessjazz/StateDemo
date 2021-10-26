#include "MovingPlatform.h"

MovingPlatform::MovingPlatform(Point2f pos, int width, int height, int direction)
	: Platform(pos, width, height),
	m_direction(direction),
	m_amplitude(4.f),
	m_frequency(0.20f),
	m_xoffset(0),
	m_yoffset(0)
{
	SetPosition(pos);
	SetType(OBJ_MOVING_PLATFORM);
	SetDrawOrder(2);
	SetHeight(height);
	SetWidth(width);
}

void MovingPlatform::Update(GameState& gState)
{
	x += 0.1f;

	if (m_direction == 0)
	{
		m_velocity.x = m_amplitude * sin(m_frequency * x + m_xoffset) + m_yoffset;
		m_pos.x += m_velocity.x;
	}
	else
	{
		m_velocity.y = m_amplitude * sin(m_frequency * x + m_xoffset) + m_yoffset;
		m_pos.y += m_velocity.y;
	}
}

void MovingPlatform::Draw(GameState& gState) const
{
	Play::DrawRect({ m_pos.x - gState.camera.x, m_pos.y - gState.camera.y }, { m_pos.x + m_width - gState.camera.x, m_pos.y + m_height - gState.camera.y }, Play::cBlack, true);
}
