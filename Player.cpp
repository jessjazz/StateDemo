#include "IdleState.h"
#include "Player.h"
#include "PlayerState.h"

Player::Player(Point2f pos)
	: GameObject(pos),
	m_speed(5),
	m_state(State::STATE_IDLE),
	m_gravity(1.0f),
	b_onGround(false)
{
	SetPosition(pos);
	SetVelocity({ 0,0 });
	SetType(OBJ_PLAYER);
	SetDrawOrder(1);
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
	
	m_pCurrentState->StateUpdate(*this, gState.platform);
}

void Player::Draw(GameState& gState) const
{
	switch (m_state)
	{
	case State::STATE_IDLE:
		Play::DrawSprite(Play::GetSpriteId("idle_7"), m_pos, 5 * gState.time);
		break;
	case State::STATE_IDLE_LEFT:
		Play::DrawSprite(Play::GetSpriteId("idle_left_7"), m_pos, 5 * gState.time);
		break;
	case State::STATE_RUN_RIGHT:
		Play::DrawSprite(Play::GetSpriteId("run_right_8"), m_pos, 12 * gState.time);
		break;
	case State::STATE_RUN_LEFT:
		Play::DrawSprite(Play::GetSpriteId("run_left_8"), m_pos, 12 * gState.time);
		break;
	case State::STATE_JUMP:
		Play::DrawSprite(Play::GetSpriteId("jump_right_1"), m_pos, 1);
		break;
	case State::STATE_JUMP_LEFT:
		Play::DrawSprite(Play::GetSpriteId("jump_left_1"), m_pos, 1);
		break;
	case State::STATE_CROUCH:
		Play::DrawSprite(Play::GetSpriteId("crouch_6"), m_pos, 5 * gState.time);
		break;
	case State::STATE_CROUCH_LEFT:
		Play::DrawSprite(Play::GetSpriteId("crouch_left_6"), m_pos, 5 * gState.time);
		break;
	case State::STATE_DASH_RIGHT:
		Play::DrawSprite(Play::GetSpriteId("dash_right_4"), m_pos, 10 * gState.time);
		break;
	case State::STATE_DASH_LEFT:
		Play::DrawSprite(Play::GetSpriteId("dash_left_4"), m_pos, 10 * gState.time);
		break;
	case State::STATE_CRAWL_RIGHT:
		Play::DrawSprite(Play::GetSpriteId("crawl_right_8"), m_pos, 10 * gState.time);
		break;
	case State::STATE_CRAWL_LEFT:
		Play::DrawSprite(Play::GetSpriteId("crawl_left_8"), m_pos, 10 * gState.time);
		break;
	case State::STATE_SLIDE_RIGHT:
		Play::DrawSprite(Play::GetSpriteId("slide_right_4"), m_pos, 10 * gState.time);
		break;
	case State::STATE_SLIDE_LEFT:
		Play::DrawSprite(Play::GetSpriteId("slide_left_4"), m_pos, 10 * gState.time);
		break;
	case State::STATE_FALL_RIGHT:
		Play::DrawSprite(Play::GetSpriteId("fall_right_1"), m_pos, 1);
		break;
	case State::STATE_FALL_LEFT:
		Play::DrawSprite(Play::GetSpriteId("fall_left_1"), m_pos, 1);
		break;
	default:
		break;
	}
}

bool Player::IsColliding(GameObject& object1, GameObject* object2)
{
	int object1_y = object1.GetPosition().y;
	int object1_x = object1.GetPosition().x;
	int object2_x = object2->GetPosition().x;
	int object2_y = object2->GetPosition().y;
	
	int object1_w = object1.GetWidth();
	int object1_h = object1.GetHeight();
	int object2_w = object2->GetWidth();
	int object2_h = object2->GetHeight();


	if (object1_x < object2_x + object2_w &&
		object1_x + object1_w > object2_x &&
		object1_y < object2_y + object2_h &&
		object1_y + object1_h > object2_y)
	{
		return true;
	}

	return false;
}
