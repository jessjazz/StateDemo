#include "Door.h"

Door::Door(Point2f pos)
	: GameObject(pos)
{
	SetPosition(pos);
	SetType(OBJ_DOOR);
	SetDrawOrder(4);
}

void Door::Update(GameState& gState)
{
	// If player presses e or E
	if (Play::KeyPressed(0x45) || Play::KeyPressed(0x65))
	{
		m_state = OPENING;
	}

	if (m_state == OPENING)
	{
		m_framePos += m_animSpeed;

		if (m_framePos > 1.0f)
		{
			m_frame++;
			m_framePos -= 1.0f;
		}
	}

	if (m_frame >= Play::GetSpriteFrames(gState.sprites.door) - 1)
	{
		m_state = OPEN;
	}
}

void Door::Draw(GameState& gState) const
{
	switch (m_state)
	{
	case CLOSED:
		Play::DrawSprite(gState.sprites.door, { m_pos.x - gState.camera.x, m_pos.y - gState.camera.y }, 0);
		break;
	case OPENING:
		Play::DrawSprite(gState.sprites.door, { m_pos.x - gState.camera.x, m_pos.y - gState.camera.y }, m_frame);
		break;
	case OPEN:
		Play::DrawSprite(gState.sprites.door, { m_pos.x - gState.camera.x, m_pos.y - gState.camera.y }, 3);
		break;
	default:
		break;
	}
}
