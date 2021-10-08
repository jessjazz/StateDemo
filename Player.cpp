#include "Player.h"
#include "PlayerState.h"
#include "IdleState.h"
#include "JumpingState.h"
#include "CrouchingState.h"
#include "RunLeftState.h"
#include "RunRightState.h"

IdleState Player::s_idleState;
JumpingState Player::s_jumpingState;
CrouchingState Player::s_crouchingState;
RunRightState Player::s_runRightState;
RunLeftState Player::s_runLeftState;


Player::Player(Point2f pos)
	: GameObject(pos), 
	m_speed(5),
	m_state(State::STATE_INVALID),
	m_pendingState(State::STATE_IDLE),
	m_pCurrentState(&s_idleState)
{
	SetPosition(pos);
	SetType(OBJ_PLAYER);
	SetState(State::STATE_IDLE);
}

Player::~Player() {}

void Player::Update(GameState& gState)
{
	m_pCurrentState->HandleInput(*this);

	if (m_pendingState != m_state)
	{
		switch (m_pendingState)
		{
		case State::STATE_IDLE:
			m_pCurrentState = &s_idleState;
			break;
		case State::STATE_JUMP:
			m_pCurrentState = &s_jumpingState;
			break;
		case State::STATE_CROUCH:
			m_pCurrentState = &s_crouchingState;
			break;
		case State::STATE_RUN_RIGHT:
			m_pCurrentState = &s_runRightState;
			break;
		case State::STATE_RUN_LEFT:
			m_pCurrentState = &s_runLeftState;
			break;
		default:
			break;
		}

		m_state = m_pendingState;
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
	}
}

void Player::SetState(State newState)
{
	m_pendingState = newState;
}

int Player::GetSpeed() const
{
	return m_speed;
}
