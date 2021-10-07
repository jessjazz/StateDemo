#include "Player.h"
#include "PlayerState.h"

Player::Player(Point2f pos)
	: GameObject(pos)
{
	m_pos = pos;
	SetType(OBJ_PLAYER);
}

Player::~Player() {}

void Player::Update(GameState& gState)
{
	PlayBlitter& blit = PlayBlitter::Instance();
	PlayBuffer& buff = PlayBuffer::Instance();

	switch (gState.playerState)
	{
	case STATE_IDLE:
		if (buff.KeyDown(VK_RIGHT))
		{
			gState.playerState = STATE_RUN_RIGHT;
			m_pos.x += 5;
		}
		else if (buff.KeyDown(VK_LEFT))
		{
			gState.playerState = STATE_RUN_LEFT;
			m_pos.x -= 5;
		}
		else if (buff.KeyPressed(VK_SPACE))
		{
			gState.playerState = STATE_JUMP;
			m_pos.y -= 20;
		}
		else if (buff.KeyPressed(VK_DOWN))
		{
			gState.playerState = STATE_CROUCH;
		}
		break;

	case STATE_RUN_RIGHT:
		if (buff.KeyDown(VK_RIGHT))
		{
			m_pos.x += 5;
		}
		else if (!buff.KeyDown(VK_RIGHT))
		{
			gState.playerState = STATE_IDLE;
		}
		break;

	case STATE_RUN_LEFT:
		if (buff.KeyDown(VK_LEFT))
		{
			m_pos.x -= 5;
		}
		else if (!buff.KeyDown(VK_LEFT))
		{
			gState.playerState = STATE_IDLE;
		}
		break;

	case STATE_JUMP:
		if (!buff.KeyDown(VK_SPACE))
		{
			gState.playerState = STATE_IDLE;
			m_pos.y += 20;
		}
		break;

	case STATE_CROUCH:
		if (!buff.KeyDown(VK_DOWN))
		{
			gState.playerState = STATE_IDLE;
		}
		break;

	default:
		break;
	}

	gState.player->SetPosition(m_pos);
}

void Player::Draw(GameState& gState) const
{
	PlayBlitter& blit = PlayBlitter::Instance();

	switch (gState.playerState)
	{
	case STATE_IDLE:
		blit.Draw(blit.GetSpriteId("idle_7"), m_pos, 5.0f * gState.time);
		break;
	case STATE_RUN_RIGHT:
		blit.Draw(blit.GetSpriteId("run_right_8"), m_pos, 12.0f * gState.time);
		break;
	case STATE_RUN_LEFT:
		blit.Draw(blit.GetSpriteId("run_left_8"), m_pos, 12.0f * gState.time);
		break;
	case STATE_JUMP:
		blit.Draw(blit.GetSpriteId("jump_2"), m_pos, 10.0f * gState.time);
		break;
	case STATE_CROUCH:
		blit.Draw(blit.GetSpriteId("crouch_2"), m_pos, 5.0f * gState.time);
	}
}
