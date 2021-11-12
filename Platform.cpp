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
{}

void Platform::Draw(GameState& gState) const
{
	// Draw rectangle according to parameters set in MainGame CreateMap function
	Play::DrawRect({ m_pos.x - gState.camera.x, m_pos.y - gState.camera.y }, { m_pos.x + m_width - gState.camera.x, m_pos.y + m_height - gState.camera.y }, Play::cGrey, true);
}

Platform* Platform::CreatePlatform(Point2f pos, int width, int height)
{
	return new Platform(pos, width, height);
}
