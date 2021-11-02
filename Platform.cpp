#include "Platform.h"
#include "MainGame.h"

Platform::Platform(Point2f pos, int width, int height)
	: GameObject(pos)
{
	SetPosition(pos);
	SetType(OBJ_PLATFORM);
	SetDrawOrder(3);
	SetHeight(height);
	SetWidth(width);
}

void Platform::Update(GameState& gState)
{
}

void Platform::Draw(GameState& gState) const
{
	Play::DrawRect({ m_pos.x - gState.camera.x, m_pos.y - gState.camera.y }, { m_pos.x + m_width - gState.camera.x, m_pos.y + m_height - gState.camera.y }, Play::cGrey, true);
}
