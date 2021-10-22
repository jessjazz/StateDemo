#include "IdleState.h"
#include "Player.h"
#include "PlayerState.h"

Player::Player(Point2f pos)
	: GameObject(pos),
	m_speed(5),
	m_state(State::STATE_IDLE),
	m_gravity({ 0, 1 }),
	b_onGround(false),
	b_isDead(false)
{
	SetPosition(pos);
	SetVelocity({ 0,0 });
	SetType(OBJ_PLAYER);
	SetDrawOrder(1);
	m_pCurrentState = new IdleRightState;
}

Player::~Player() {}

void Player::Update(GameState& gState)
{
	if (!b_isDead)
	{
		PlayerState* pState = m_pCurrentState->HandleInput(*this);

		if (pState != nullptr)
		{
			delete m_pCurrentState;
			m_pCurrentState = pState;
		}

		m_pCurrentState->StateUpdate(*this, gState.s_vMap, gState);
	}
	else
	{
		HandleGameOver();
	}
}

void Player::Draw(GameState& gState) const
{
	switch (m_state)
	{
	case State::STATE_IDLE:
		Play::DrawSprite(gState.sprites.idleRight, m_pos, 5 * gState.time);
		break;
	case State::STATE_IDLE_LEFT:
		Play::DrawSprite(gState.sprites.idleLeft, m_pos, 5 * gState.time);
		break;
	case State::STATE_RUN_RIGHT:
		Play::DrawSprite(gState.sprites.runRight, m_pos, 12 * gState.time);
		break;
	case State::STATE_RUN_LEFT:
		Play::DrawSprite(gState.sprites.runLeft, m_pos, 12 * gState.time);
		break;
	case State::STATE_JUMP:
		Play::DrawSprite(gState.sprites.jumpRight, m_pos, 1);
		break;
	case State::STATE_JUMP_LEFT:
		Play::DrawSprite(gState.sprites.jumpLeft, m_pos, 1);
		break;
	case State::STATE_CROUCH:
		Play::DrawSprite(gState.sprites.crouchRight, m_pos, 5 * gState.time);
		break;
	case State::STATE_CROUCH_LEFT:
		Play::DrawSprite(gState.sprites.crouchLeft, m_pos, 5 * gState.time);
		break;
	case State::STATE_DASH_RIGHT:
		Play::DrawSprite(gState.sprites.dashRight, m_pos, 10 * gState.time);
		break;
	case State::STATE_DASH_LEFT:
		Play::DrawSprite(gState.sprites.dashLeft, m_pos, 10 * gState.time);
		break;
	case State::STATE_CRAWL_RIGHT:
		Play::DrawSprite(gState.sprites.crawlRight, m_pos, 10 * gState.time);
		break;
	case State::STATE_CRAWL_LEFT:
		Play::DrawSprite(gState.sprites.crawlLeft, m_pos, 10 * gState.time);
		break;
	case State::STATE_SLIDE_RIGHT:
		Play::DrawSprite(gState.sprites.slideRight, m_pos, 10 * gState.time);
		break;
	case State::STATE_SLIDE_LEFT:
		Play::DrawSprite(gState.sprites.slideLeft, m_pos, 10 * gState.time);
		break;
	case State::STATE_FALL_RIGHT:
		Play::DrawSprite(gState.sprites.fallRight, m_pos, 1);
		break;
	case State::STATE_FALL_LEFT:
		Play::DrawSprite(gState.sprites.fallLeft, m_pos, 1);
		break;
	default:
		break;
	}
}

bool Player::IsStandingOn(const GameObject* object1, const GameObject* object2) const
{
	PLAY_ASSERT_MSG(object1, "object1 cannot be null");
	PLAY_ASSERT_MSG(object2, "object2 cannot be null");

	int xoffset = 5;
	int vert_dist = 15;

	int object1_x1 = object1->GetPosition().x - xoffset;
	int object1_y1 = object1->GetPosition().y + object1->GetHeight();
	int object1_x2 = object1->GetPosition().x + object1->GetWidth() + xoffset;
	int object1_y2 = object1->GetPosition().y + object1->GetHeight() + vert_dist;

	int object2_x1 = object2->GetPosition().x;
	int object2_y1 = object2->GetPosition().y;
	int object2_x2 = object2->GetPosition().x + object2->GetWidth();
	int object2_y2 = object2->GetPosition().y + vert_dist;


	if (object1_x1 < object2_x2 &&
		object1_x2 > object2_x1 &&
		object1_y1 < object2_y2 &&
		object1_y2 > object2_y1)
	{
		return true;
	}

	return false;
}

void Player::HandleGameOver()
{
	Play::CentreSpriteOrigin("151px");
	Play::CentreSpriteOrigin("64px");
	Play::DrawFontText("151px", "Game Over", { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2 }, Play::CENTRE);
	Play::DrawFontText("64px", "Press enter to play again!", { DISPLAY_WIDTH / 2, 510 }, Play::CENTRE);

	if (Play::KeyPressed(VK_RETURN))
	{
		m_pos = { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT - 140 };
		b_isDead = false;
		SetDrawState(State::STATE_IDLE);
		m_pCurrentState = new IdleRightState;
	}
}

