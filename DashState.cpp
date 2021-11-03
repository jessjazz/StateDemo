#include "DashState.h"
#include "FallState.h"
#include "RunningState.h"
#include "Player.h"

constexpr float MAX_DASH = 10.0f;

PlayerState* DashRightState::HandleInput(Player& player)
{
	m_dashTime++;

	if (m_dashTime > MAX_DASH)
	{
		return new RunRightState;
	}

	if (!player.IsGrounded())
	{
		return new FallRightState;
	}

	return nullptr;
}

void DashRightState::StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const
{
	// Set sprite dimensions
	int spriteId = gState.sprites.dashRight;
	player.SetHeight(Play::GetSpriteHeight(spriteId));
	player.SetWidth(Play::GetSpriteWidth(spriteId));

	int speed = player.GetSpeed() * 2;

	HandleCollision(player, map, speed, RIGHT);
	HandleCoinPickup(player, gState);
	HandleGemPickup(player, gState);
}

void DashRightState::Enter(Player& player) const
{
	player.SetDrawState(State::STATE_DASH_RIGHT);
}

PlayerState* DashLeftState::HandleInput(Player& player)
{
	m_dashTime++;

	if (m_dashTime > MAX_DASH)
	{
		return new RunLeftState;
	}

	if (!player.IsGrounded())
	{
		return new FallLeftState;
	}

	return nullptr;
}

void DashLeftState::StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const
{
	// Set sprite dimensions
	int spriteId = gState.sprites.dashLeft;
	player.SetHeight(Play::GetSpriteHeight(spriteId));
	player.SetWidth(Play::GetSpriteWidth(spriteId));

	int speed = player.GetSpeed() * 2;

	HandleCollision(player, map, speed, LEFT);
	HandleCoinPickup(player, gState);
	HandleGemPickup(player, gState);
}

void DashLeftState::Enter(Player& player) const
{
	player.SetDrawState(State::STATE_DASH_LEFT);
}
