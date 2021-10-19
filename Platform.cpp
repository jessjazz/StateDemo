#include "Platform.h"

Platform::Platform(Point2f pos)
	: GameObject(pos)
{
	SetPosition(pos);
	SetType(OBJ_PLATFORM);
	SetDrawOrder(2);
	SetHeight(50);
	SetWidth(800);
}

void Platform::Update(GameState& gState)
{
}

void Platform::Draw(GameState& gState) const
{
	Play::DrawRect(m_pos, { m_pos.x + m_width, m_pos.y + m_height }, Play::cWhite, true);
}
