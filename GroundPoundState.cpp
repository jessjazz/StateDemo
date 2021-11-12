#include "GroundPoundState.h"
#include "FallState.h"
#include "IdleState.h"
#include "DestructiblePlatform.h"
#include "Player.h"

constexpr float MAX_SMASH = 4.f; // Change this if animation speed is changed

PlayerState* GroundPoundState::HandleInput(Player& player)
{
	m_smashTime += 0.1f;

	switch (m_direction)
	{
	case RIGHT:
		if (m_smashTime > MAX_SMASH || !player.IsGrounded())
		{
			return new FallState(RIGHT);
		}
		return nullptr;
		break;
	case LEFT:
		if (m_smashTime > MAX_SMASH || !player.IsGrounded())
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

void GroundPoundState::StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const
{
	int spriteId;
	
	switch (m_direction)
	{
	case RIGHT:
		// Set sprite dimensions
		spriteId = gState.sprites.groundPoundRight;
		player.SetHeight(Play::GetSpriteHeight(spriteId));
		player.SetWidth(Play::GetSpriteWidth(spriteId));
		break;
	case LEFT:
		// Set sprite dimensions
		spriteId = gState.sprites.groundPoundLeft;
		player.SetHeight(Play::GetSpriteHeight(spriteId));
		player.SetWidth(Play::GetSpriteWidth(spriteId));
		break;
	}

	HandleCollision(player, map);
}

void GroundPoundState::Enter(Player& player) const
{
	switch (m_direction)
	{
	case RIGHT:
		player.SetDrawState(State::STATE_SMASH_RIGHT);
		break;
	case LEFT:
		player.SetDrawState(State::STATE_SMASH_LEFT);
		break;
	}
	// Resets animation on state entry
	player.SetFrame(0);
	player.SetAnimSpeed(0.25f);
	Play::PlayAudio("smash");
}

void GroundPoundState::HandleCollision(Player& player, const std::vector<GameObject*>& map) const
{
	Point2f currentPos = player.GetPosition();;

	for (GameObject* p : map)
	{
		if (IsStandingOn(&player, p))
		{
			// Fall off decaying platform if it disappears while smashing
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
				// Destroy platform if on top of it
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