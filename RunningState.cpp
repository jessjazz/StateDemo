#include "DashState.h"
#include "FallState.h"
#include "IdleState.h"
#include "JumpingState.h"
#include "RunningState.h"
#include "SlideState.h"
#include "Player.h"

PlayerState* RunState::HandleInput(Player& player)
{
	switch (m_direction)
	{
	case RIGHT:
		if (!Play::KeyDown(VK_RIGHT))
		{
			return new IdleState(RIGHT);
		}

		if (Play::KeyPressed(VK_SHIFT))
		{
			return new DashState(RIGHT);
		}

		if (Play::KeyPressed(VK_DOWN))
		{
			return new SlideState(RIGHT);
		}

		if (Play::KeyPressed(VK_SPACE))
		{
			return new JumpState(RIGHT);
		}

		if (!player.IsGrounded())
		{
			return new FallState(RIGHT);
		}

		return nullptr;
		break;

	case LEFT:
		if (!Play::KeyDown(VK_LEFT))
		{
			return new IdleState(LEFT);
		}

		if (Play::KeyPressed(VK_SHIFT))
		{
			return new DashState(LEFT);
		}

		if (Play::KeyPressed(VK_DOWN))
		{
			return new SlideState(LEFT);
		}

		if (Play::KeyPressed(VK_SPACE))
		{
			return new JumpState(LEFT);
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

void RunState::StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const
{
	int spriteId;
	int speed = player.GetSpeed();

	switch (m_direction)
	{
	case RIGHT:
		// Set sprite dimensions
		spriteId = gState.sprites.runRight;
		player.SetHeight(Play::GetSpriteHeight(spriteId));
		player.SetWidth(Play::GetSpriteWidth(spriteId));
		HandleCollision(player, map, speed, RIGHT);
		break;
	case LEFT:
		// Set sprite dimensions
		spriteId = gState.sprites.runLeft;
		player.SetHeight(Play::GetSpriteHeight(spriteId));
		player.SetWidth(Play::GetSpriteWidth(spriteId));
		HandleCollision(player, map, speed, LEFT);
		break;
	}

	HandleCoinPickup(player, gState);
	HandleGemPickup(player, gState);
}

void RunState::Enter(Player& player) const
{
	switch (m_direction)
	{
	case RIGHT:
		player.SetDrawState(State::STATE_RUN_RIGHT);
		break;
	case LEFT:
		player.SetDrawState(State::STATE_RUN_LEFT);
		break;
	}

	player.SetCrouching(false);
}