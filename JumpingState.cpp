#include "FallState.h"
#include "JumpingState.h"
#include "Player.h"

constexpr float MAX_JUMP_TIME = 10.0f;
constexpr int JUMP_HEIGHT = 10;
constexpr int JUMP_DISTANCE = 5;

PlayerState* JumpState::HandleInput(Player& player)
{
	m_jumpTime++;
	
	switch (m_direction)
	{
	case RIGHT:
		if (!Play::KeyDown(VK_SPACE) || m_jumpTime > MAX_JUMP_TIME)
		{
			return new FallState(RIGHT);
		}
		return nullptr;
		break;

	case LEFT:
		if (!Play::KeyDown(VK_SPACE) || m_jumpTime > MAX_JUMP_TIME)
		{
			return new FallState(LEFT);
		}
		return nullptr;
		break;

	default:
		return nullptr;
		break;
	}
}

void JumpState::StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const
{
	int spriteId;
	Point2f currentPos = player.GetPosition();

	switch (m_direction)
	{
	case RIGHT:
		// Set sprite dimensions
		spriteId = gState.sprites.jumpRight;
		player.SetHeight(Play::GetSpriteHeight(spriteId));
		player.SetWidth(Play::GetSpriteWidth(spriteId));

		if (!player.IsGrounded() && Play::KeyDown(VK_RIGHT))
		{
			player.SetVelocity({ JUMP_DISTANCE, player.GetVelocity().y });
		}
		break;
	case LEFT:
		// Set sprite dimensions
		spriteId = gState.sprites.jumpLeft;
		player.SetHeight(Play::GetSpriteHeight(spriteId));
		player.SetWidth(Play::GetSpriteWidth(spriteId));

		if (!player.IsGrounded() && Play::KeyDown(VK_LEFT))
		{
			player.SetVelocity({ -JUMP_DISTANCE, player.GetVelocity().y });
		}
		break;
	}

	if (player.IsGrounded())
	{
		player.SetVelocity({ 0, player.GetVelocity().y - JUMP_HEIGHT });
	}
	
	HandleCoinPickup(player, gState);
	HandleGemPickup(player, gState);
	player.SetPosition(currentPos + player.GetVelocity());
	HandleJumpCollision(player, map);
	player.SetGrounded(false);
}

void JumpState::Enter(Player& player) const
{
	switch (m_direction)
	{
	case RIGHT:
		player.SetDrawState(State::STATE_JUMP);
		break;
	case LEFT:
		player.SetDrawState(State::STATE_JUMP_LEFT);
		break;
	}

	player.SetCrouching(false);
	Play::PlayAudio("jump");
}

void JumpState::HandleJumpCollision(Player& player, const std::vector<GameObject*>& map) const
{
	for (GameObject* p : map)
	{
		if (DetectCollision(&player, p, player.IsCrouching()) == UP && p->IsCollidable())
		{
			player.SetVelocity({ player.GetVelocity().x, player.GetVelocity().y * -1.f });
		}
		else if (DetectCollision(&player, p, player.IsCrouching()) == LEFT || DetectCollision(&player, p, player.IsCrouching()) == RIGHT && p->IsCollidable())
		{
			player.SetVelocity({ player.GetVelocity().x * -0.5f, player.GetVelocity().y });
		}
	}

	if (player.GetPosition().x > LEVEL_WIDTH - player.GetWidth())
	{
		player.SetPosition({ LEVEL_WIDTH - player.GetWidth(), player.GetPosition().y });
	}
	else if (player.GetPosition().x < 0)
	{
		player.SetPosition({ 0, player.GetPosition().y });
	}
}