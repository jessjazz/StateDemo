#include "IdleState.h"
#include "Player.h"
#include "PlayerState.h"

Player::Player(Point2f pos)
	: GameObject(pos), 
	m_speed(5),
	m_state(State::STATE_IDLE)
{
	SetPosition(pos);
	SetType(OBJ_PLAYER);
	m_pCurrentState = new IdleState;
}

Player::~Player() {}

void Player::Update(GameState& gState)
{
	PlayerState* pState = m_pCurrentState->HandleInput(*this);

	if (pState != nullptr)
	{
		delete m_pCurrentState;
		m_pCurrentState = pState;
	}
	
	m_pCurrentState->StateUpdate(*this);
}

void Player::Draw(GameState& gState) const
{

	switch (m_state)
	{
	case State::STATE_IDLE:
		Play::DrawSprite(Play::GetSpriteId("large_idle_7"), m_pos, 5.0f * gState.time);
		break;
	case State::STATE_RUN_RIGHT:
		Play::DrawSprite(Play::GetSpriteId("large_run_right_8"), m_pos, 12.0f * gState.time);
		break;
	case State::STATE_RUN_LEFT:
		Play::DrawSprite(Play::GetSpriteId("large_run_left_8"), m_pos, 12.0f * gState.time);
		break;
	case State::STATE_JUMP:
		Play::DrawSprite(Play::GetSpriteId("large_jump_3"), m_pos, 8.0f * gState.time);
		break;
	case State::STATE_CROUCH:
		Play::DrawSprite(Play::GetSpriteId("large_crouch_6"), m_pos, 5.0f * gState.time);
		break;
	case State::STATE_DASH_RIGHT:
		Play::DrawSprite(Play::GetSpriteId("large_dash_right_4"), m_pos, 10.0f * gState.time);
		break;
	case State::STATE_DASH_LEFT:
		Play::DrawSprite(Play::GetSpriteId("large_dash_left_4"), m_pos, 10.0f * gState.time);
		break;
	case State::STATE_CRAWL_RIGHT:
		Play::DrawSprite(Play::GetSpriteId("large_crawl_right_8"), m_pos, 10.0f * gState.time);
		break;
	case State::STATE_CRAWL_LEFT:
		Play::DrawSprite(Play::GetSpriteId("large_crawl_left_8"), m_pos, 10.0f * gState.time);
		break;
	default:
		break;
	}
}

void Player::SetState(PlayerState* playerState)
{
	m_pCurrentState = playerState;
}

void Player::SetDrawState(State state)
{
	m_state = state;
}

PlayerState* Player::GetState() const
{
	return m_pCurrentState;
}

int Player::GetSpeed() const
{
	return m_speed;
}
