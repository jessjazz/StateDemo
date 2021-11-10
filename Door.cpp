#include "Door.h"
#include "Player.h"

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
	if ((Play::KeyPressed('e') || Play::KeyPressed('E')) && m_state == CLOSED)
	{
		// Get coin count and only open the door if all coins have been collected
		int maxCoins = GameObject::GetObjectCount(Type::OBJ_COIN);
		std::vector<GameObject*> players;
		GameObject::GetObjectList(Type::OBJ_PLAYER, players);
		for (GameObject* p : players)
		{
			Player* player = static_cast<Player*>(p);
			if (player->GetCoinCount() == maxCoins)
			{
				m_state = OPENING;
				Play::PlayAudio("door");
			}
		}
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

Door* Door::CreateDoor(Point2f pos)
{
	return new Door(pos);
}
