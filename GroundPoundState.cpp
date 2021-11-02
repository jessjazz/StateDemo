#include "GroundPoundState.h"
#include "FallState.h"
#include "IdleState.h"
#include "DestructiblePlatform.h"
#include "Player.h"

constexpr float MAX_SMASH = 4.f;

PlayerState* GroundPoundRightState::HandleInput(Player& player)
{
	m_smashTime += 0.1f;
	if (m_smashTime > MAX_SMASH)
	{
		player.SetDrawState(State::STATE_FALL_RIGHT);
		return new FallRightState;
	}
	return nullptr;
}

void GroundPoundRightState::StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const
{
	// Set sprite dimensions
	int spriteId = gState.sprites.groundPoundRight;
	player.SetHeight(Play::GetSpriteHeight(spriteId));
	player.SetWidth(Play::GetSpriteWidth(spriteId));

	HandleCollision(player, map);
}

void GroundPoundRightState::HandleCollision(Player& player, const std::vector<GameObject*>& map) const
{
	Point2f currentPos = player.GetPosition();;

	for (GameObject* p : map)
	{
		if (IsStandingOn(&player, p))
		{
			if (p->GetType() == GameObject::Type::OBJ_DECAYING_PLATFORM)
			{
				if (p->IsCollidable())
				{
					player.SetPosition({ currentPos.x, p->GetPosition().y - player.GetHeight() });
					player.SetVelocity({ 0,0 });
					player.SetGrounded(true);
				}
				else
				{
					player.SetGrounded(false);
				}
			}
			else if (p->GetType() == GameObject::Type::OBJ_DESTRUCTIBLE_PLATFORM && p->IsCollidable())
			{
				DestructiblePlatform* dp = static_cast<DestructiblePlatform*>(p);
				if (dp->GetState() == DestructiblePlatform::State::STATE_APPEAR && m_smashTime > MAX_SMASH - 0.2f)
				{
					dp->SetState(DestructiblePlatform::State::STATE_BROKEN);
					player.SetGrounded(false);
				}
			}
			else
			{
				player.SetPosition({ currentPos.x, p->GetPosition().y - player.GetHeight() });
				player.SetVelocity({ 0,0 });
				player.SetGrounded(true);
			}
		}
	}
}

PlayerState* GroundPoundLeftState::HandleInput(Player& player)
{
	m_smashTime += 0.1f;
	if (m_smashTime > MAX_SMASH)
	{
		player.SetDrawState(State::STATE_FALL_LEFT);
		return new FallLeftState;
	}
	return nullptr;
}

void GroundPoundLeftState::StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const
{
	// Set sprite dimensions
	int spriteId = gState.sprites.groundPoundLeft;
	player.SetHeight(Play::GetSpriteHeight(spriteId));
	player.SetWidth(Play::GetSpriteWidth(spriteId));

	GroundPoundLeftState::HandleCollision(player, map);
}

void GroundPoundLeftState::HandleCollision(Player& player, const std::vector<GameObject*>& map) const
{
	Point2f currentPos = player.GetPosition();;

	for (GameObject* p : map)
	{
		if (IsStandingOn(&player, p))
		{
			if (p->GetType() == GameObject::Type::OBJ_DECAYING_PLATFORM)
			{
				if (p->IsCollidable())
				{
					player.SetPosition({ currentPos.x, p->GetPosition().y - player.GetHeight() });
					player.SetVelocity({ 0,0 });
					player.SetGrounded(true);
				}
				else
				{
					player.SetGrounded(false);
				}
			}
			else if (p->GetType() == GameObject::Type::OBJ_DESTRUCTIBLE_PLATFORM && p->IsCollidable())
			{
				DestructiblePlatform* dp = static_cast<DestructiblePlatform*>(p);
				if (dp->GetState() == DestructiblePlatform::State::STATE_APPEAR && m_smashTime > MAX_SMASH - 0.2f)
				{
					dp->SetState(DestructiblePlatform::State::STATE_BROKEN);
					player.SetGrounded(false);
				}
			}
			else
			{
				player.SetPosition({ currentPos.x, p->GetPosition().y - player.GetHeight() });
				player.SetVelocity({ 0,0 });
				player.SetGrounded(true);
			}
		}
	}
}
