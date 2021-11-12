#include "MovingPlatform.h"

MovingPlatform::MovingPlatform(Point2f pos, int width, int height, int direction, float sinAmplitude, float sinFrequency)
	: Platform(pos, width, height),
	m_direction(direction),
	m_amplitude(sinAmplitude),
	m_frequency(sinFrequency)
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

	if (m_direction == VERTICAL)
	{
		// Vertical sine wave controls x velocity
		m_velocity.x = m_amplitude * sin(m_frequency * x + m_xoffset) + m_yoffset;
		m_pos.x += m_velocity.x;
	}
	else
	{
		// Horizontal sine wave controls y velocity
		m_velocity.y = m_amplitude * sin(m_frequency * x + m_xoffset) + m_yoffset;
		m_pos.y += m_velocity.y;
	}
}

void MovingPlatform::Draw(GameState& gState) const
{
	// Draw rectangle according to parameters set in MainGame CreateMap function
	Play::DrawRect({ m_pos.x - gState.camera.x, m_pos.y - gState.camera.y }, { m_pos.x + m_width - gState.camera.x, m_pos.y + m_height - gState.camera.y }, Play::cBlack, true);
}

MovingPlatform* MovingPlatform::CreatePlatform(Point2f pos, int width, int height, int direction, float sinAmplitude, float sinFrequency)
{
	return new MovingPlatform(pos, width, height, direction, sinAmplitude, sinFrequency);
}
