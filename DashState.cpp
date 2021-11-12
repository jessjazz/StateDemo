#include "DashState.h"
#include "FallState.h"
#include "RunningState.h"
#include "Player.h"

constexpr float MAX_DASH = 10.0f;

PlayerState* DashState::HandleInput(Player& player)
{
	m_dashTime++;
	
	switch (m_direction)
	{
	case RIGHT:
		if (m_dashTime > MAX_DASH)
		{
			return new RunState(RIGHT);
		}

		if (!player.IsGrounded())
		{
			return new FallState(RIGHT);
		}

		return nullptr;
		break;

	case LEFT:
		if (m_dashTime > MAX_DASH)
		{
			return new RunState(LEFT);
		}

		if (!player.IsGrounded())
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

void DashState::StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const
{
	int spriteId;
	int speed = player.GetSpeed() * 2;

	switch (m_direction)
	{
	case RIGHT:
		// Set sprite dimensions
		spriteId = gState.sprites.dashRight;
		player.SetHeight(Play::GetSpriteHeight(spriteId));
		player.SetWidth(Play::GetSpriteWidth(spriteId));
		HandleCollision(player, map, speed, RIGHT);
		break;
	case LEFT:
		// Set sprite dimensions
		spriteId = gState.sprites.dashLeft;
		player.SetHeight(Play::GetSpriteHeight(spriteId));
		player.SetWidth(Play::GetSpriteWidth(spriteId));
		HandleCollision(player, map, speed, LEFT);
		break;
	}

	HandleCoinPickup(player, gState);
	HandleGemPickup(player, gState);
}

void DashState::Enter(Player& player) const
{
	switch (m_direction)
	{
	case RIGHT:
		player.SetDrawState(State::STATE_DASH_RIGHT);
		break;
	case LEFT:
		player.SetDrawState(State::STATE_DASH_LEFT);
		break;
	}
}