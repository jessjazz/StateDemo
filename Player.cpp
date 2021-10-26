#include "IdleState.h"
#include "Player.h"
#include "PlayerState.h"

Player::Player(Point2f pos)
	: GameObject(pos),
	m_speed(5),
	m_state(State::STATE_IDLE),
	m_gravity({ 0, 1 }),
	b_onGround(false),
	b_isDead(false),
	m_lives(3)
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
	else if (b_isDead && m_lives > 0)
	{
		HandleLifeLost(gState);
	}
	else
	{
		HandleGameOver(gState);
	}
}

void Player::Draw(GameState& gState) const
{
	switch (m_state)
	{
	case State::STATE_IDLE:
		Play::DrawSprite(gState.sprites.idleRight, { m_pos.x - gState.camera.x, m_pos.y - gState.camera.y }, 5 * gState.time);
		break;
	case State::STATE_IDLE_LEFT:
		Play::DrawSprite(gState.sprites.idleLeft, { m_pos.x - gState.camera.x, m_pos.y - gState.camera.y }, 5 * gState.time);
		break;
	case State::STATE_RUN_RIGHT:
		Play::DrawSprite(gState.sprites.runRight, { m_pos.x - gState.camera.x, m_pos.y - gState.camera.y }, 12 * gState.time);
		break;
	case State::STATE_RUN_LEFT:
		Play::DrawSprite(gState.sprites.runLeft, { m_pos.x - gState.camera.x, m_pos.y - gState.camera.y }, 12 * gState.time);
		break;
	case State::STATE_JUMP:
		Play::DrawSprite(gState.sprites.jumpRight, { m_pos.x - gState.camera.x, m_pos.y - gState.camera.y }, 1);
		break;
	case State::STATE_JUMP_LEFT:
		Play::DrawSprite(gState.sprites.jumpLeft, { m_pos.x - gState.camera.x, m_pos.y - gState.camera.y }, 1);
		break;
	case State::STATE_CROUCH:
		Play::DrawSprite(gState.sprites.crouchRight, { m_pos.x - gState.camera.x, m_pos.y - gState.camera.y }, 5 * gState.time);
		break;
	case State::STATE_CROUCH_LEFT:
		Play::DrawSprite(gState.sprites.crouchLeft, { m_pos.x - gState.camera.x, m_pos.y - gState.camera.y }, 5 * gState.time);
		break;
	case State::STATE_DASH_RIGHT:
		Play::DrawSprite(gState.sprites.dashRight, { m_pos.x - gState.camera.x, m_pos.y - gState.camera.y }, 10 * gState.time);
		break;
	case State::STATE_DASH_LEFT:
		Play::DrawSprite(gState.sprites.dashLeft, { m_pos.x - gState.camera.x, m_pos.y - gState.camera.y }, 10 * gState.time);
		break;
	case State::STATE_CRAWL_RIGHT:
		Play::DrawSprite(gState.sprites.crawlRight, { m_pos.x - gState.camera.x, m_pos.y - gState.camera.y }, 10 * gState.time);
		break;
	case State::STATE_CRAWL_LEFT:
		Play::DrawSprite(gState.sprites.crawlLeft, { m_pos.x - gState.camera.x, m_pos.y - gState.camera.y }, 10 * gState.time);
		break;
	case State::STATE_SLIDE_RIGHT:
		Play::DrawSprite(gState.sprites.slideRight, { m_pos.x - gState.camera.x, m_pos.y - gState.camera.y }, 10 * gState.time);
		break;
	case State::STATE_SLIDE_LEFT:
		Play::DrawSprite(gState.sprites.slideLeft, { m_pos.x - gState.camera.x, m_pos.y - gState.camera.y }, 10 * gState.time);
		break;
	case State::STATE_FALL_RIGHT:
		Play::DrawSprite(gState.sprites.fallRight, { m_pos.x - gState.camera.x, m_pos.y - gState.camera.y }, 1);
		break;
	case State::STATE_FALL_LEFT:
		Play::DrawSprite(gState.sprites.fallLeft, { m_pos.x - gState.camera.x, m_pos.y - gState.camera.y }, 1);
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

int Player::DetectCollision(GameObject* object1, GameObject* object2) const
{
	PLAY_ASSERT_MSG(object1, "object1 cannot be null");
	PLAY_ASSERT_MSG(object2, "object2 cannot be null");

	int offset = 3;

	int object1_y = object1->GetPosition().y;
	int object2_y = object2->GetPosition().y;
	int object1_x = object1->GetPosition().x;
	int object2_x = object2->GetPosition().x;
	int object1_yh = object1->GetPosition().y + object1->GetHeight();
	int object2_yh = object2->GetPosition().y + object2->GetHeight();
	int object1_xw = object1->GetPosition().x + object1->GetWidth();
	int object2_xw = object2->GetPosition().x + object2->GetWidth();

	int object1_y_offset = object1->GetPosition().y + offset;
	int object2_yh_offset = object2->GetPosition().y + object2->GetHeight() - offset;

	int object1_x_offset = object1->GetPosition().x - offset;
	int object2_xw_offset = object2->GetPosition().x + object2->GetWidth() + offset;

	int object1_xw_offset = object1->GetPosition().x + object1->GetWidth() + offset;
	int object2_x_offset = object2->GetPosition().x - offset;

	// Check for collision above
	if (object1_x < object2_xw &&
		object1_xw > object2_x &&
		object1_y < object2_yh &&
		object1_y_offset > object2_yh_offset)
	{
		return 1;
	}
	// Check for collision to the left of player
	else if (object1_x_offset < object2_xw_offset &&
		object1_x > object2_xw &&
		object1_y < object2_yh &&
		object1_yh > object2_y)
	{
		return -1;
	}
	// Check for collision to right of player
	else if (object1_xw < object2_x &&
		object1_xw_offset > object2_x_offset &&
		object1_y < object2_yh &&
		object1_yh > object2_y)
	{
		return 2;
	}
	else
	{
		return 0;
	}
}

void Player::HandleGameOver(GameState& gState)
{
	Play::CentreSpriteOrigin("151px");
	Play::CentreSpriteOrigin("64px");
	Play::DrawFontText("151px", "Game Over", { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2 }, Play::CENTRE);
	Play::DrawFontText("64px", "Press enter to play again!", { DISPLAY_WIDTH / 2, 510 }, Play::CENTRE);

	if (Play::KeyPressed(VK_RETURN))
	{
		HandleLifeLost(gState);
		m_lives = 3;
	}
}

void Player::HandleLifeLost(GameState& gState)
{
	m_pos = { gState.originalPlayerPos };
	b_isDead = false;
	SetDrawState(State::STATE_IDLE);
	m_pCurrentState = new IdleRightState;
	b_onGround = true;
}

