#include "CrouchingState.h"
#include "CrawlState.h"
#include "IdleState.h"
#include "Player.h"

PlayerState* CrouchRightState::HandleInput(Player& player)
{
	if (!Play::KeyDown(VK_DOWN))
	{
		return new IdleRightState;
	}

	if (Play::KeyDown(VK_RIGHT))
	{
		return new CrawlRightState;
	}

	if (Play::KeyDown(VK_LEFT))
	{
		return new CrawlLeftState;
	}
	return nullptr;
}

void CrouchRightState::StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const
{
	// Set sprite dimensions
	int spriteId = gState.sprites.crouchRight;
	player.SetHeight(Play::GetSpriteHeight(spriteId));
	player.SetWidth(Play::GetSpriteWidth(spriteId));

	Point2f currentPos = player.GetPosition();

	for (GameObject* p : map)
	{
		if (IsStandingOn(&player, p))
		{
			player.SetPosition({ currentPos.x + p->GetVelocity().x, p->GetPosition().y - player.GetHeight() });
			player.SetGrounded(true);
		}
	}
}

void CrouchRightState::Enter(Player& player) const
{
	player.SetDrawState(State::STATE_CROUCH);
	player.SetCrouching(true);
}

PlayerState* CrouchLeftState::HandleInput(Player& player)
{
	if (!Play::KeyDown(VK_DOWN))
	{
		return new IdleLeftState;
	}

	if (Play::KeyDown(VK_RIGHT))
	{
		return new CrawlRightState;
	}

	if (Play::KeyDown(VK_LEFT))
	{
		return new CrawlLeftState;
	}
	return nullptr;
}

void CrouchLeftState::StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const
{
	// Set sprite dimensions
	int spriteId = gState.sprites.crouchLeft;
	player.SetHeight(Play::GetSpriteHeight(spriteId));
	player.SetWidth(Play::GetSpriteWidth(spriteId));

	Point2f currentPos = player.GetPosition();

	for (GameObject* p : map)
	{
		if (IsStandingOn(&player, p))
		{
			player.SetPosition({ currentPos.x + p->GetVelocity().x, p->GetPosition().y - player.GetHeight() });
			player.SetGrounded(true);
		}
	}
}

void CrouchLeftState::Enter(Player& player) const
{
	player.SetDrawState(State::STATE_CROUCH_LEFT);
	player.SetCrouching(true);
}
