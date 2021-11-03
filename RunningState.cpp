#include "DashState.h"
#include "FallState.h"
#include "IdleState.h"
#include "JumpingState.h"
#include "RunningState.h"
#include "SlideState.h"
#include "Player.h"

PlayerState* RunRightState::HandleInput(Player& player)
{
	if (!Play::KeyDown(VK_RIGHT))
	{
		return new IdleRightState;
	}

	if (Play::KeyPressed(VK_SHIFT))
	{
		return new DashRightState;
	}

	if (Play::KeyPressed(VK_DOWN))
	{
		return new SlideRightState;
	}

	if (Play::KeyPressed(VK_SPACE))
	{
		return new JumpRightState;
	}

	if (!player.IsGrounded())
	{
		return new FallRightState;
	}

	return nullptr;
}

void RunRightState::StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const
{
	// Set sprite dimensions
	int spriteId = gState.sprites.runRight;
	player.SetHeight(Play::GetSpriteHeight(spriteId));
	player.SetWidth(Play::GetSpriteWidth(spriteId));

	int speed = player.GetSpeed();

	HandleCollision(player, map, speed, RIGHT);
	HandleCoinPickup(player, gState);
	HandleGemPickup(player, gState);
}

void RunRightState::Enter(Player& player) const
{
	player.SetDrawState(State::STATE_RUN_RIGHT);
	player.SetCrouching(false);
}

PlayerState* RunLeftState::HandleInput(Player& player)
{
	if (!Play::KeyDown(VK_LEFT))
	{
		return new IdleLeftState;
	}

	if (Play::KeyPressed(VK_SHIFT))
	{
		return new DashLeftState;
	}

	if (Play::KeyPressed(VK_DOWN))
	{
		return new SlideLeftState;
	}

	if (Play::KeyPressed(VK_SPACE))
	{
		return new JumpLeftState;
	}

	if (!player.IsGrounded())
	{
		return new FallLeftState;
	}

	return nullptr;
}

void RunLeftState::StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const
{
	// Set sprite dimensions
	int spriteId = gState.sprites.runLeft;
	player.SetHeight(Play::GetSpriteHeight(spriteId));
	player.SetWidth(Play::GetSpriteWidth(spriteId));

	int speed = player.GetSpeed();

	HandleCollision(player, map, speed, LEFT);
	HandleCoinPickup(player, gState);
	HandleGemPickup(player, gState);
}

void RunLeftState::Enter(Player& player) const
{
	player.SetDrawState(State::STATE_RUN_LEFT);
	player.SetCrouching(false);
}
