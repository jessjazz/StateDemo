#include "FallState.h"
#include "Player.h"
#include "IdleState.h"

PlayerState* FallState::HandleInput(Player& player)
{
	switch (m_direction)
	{
	case RIGHT:
		if (player.IsGrounded())
		{
			return new IdleState(RIGHT);
		}
		return nullptr;
		break;
		
	case LEFT:
		if (player.IsGrounded())
		{
			return new IdleState(LEFT);
		}
		return nullptr;
		break;
	default:
		return nullptr;
		break;
	}
}

void FallState::StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const
{
	int spriteId;
	Point2f currentPos = player.GetPosition();

	switch (m_direction)
	{
	case RIGHT:
		// Set sprite dimensions
		spriteId = gState.sprites.fallRight;
		player.SetHeight(Play::GetSpriteHeight(spriteId));
		player.SetWidth(Play::GetSpriteWidth(spriteId));
		break;
	case LEFT:
		// Set sprite dimensions
		spriteId = gState.sprites.fallLeft;
		player.SetHeight(Play::GetSpriteHeight(spriteId));
		player.SetWidth(Play::GetSpriteWidth(spriteId));
		break;
	}
	
	player.SetVelocity(player.GetVelocity() + player.GetGravity());
	player.SetPosition(currentPos + player.GetVelocity());

	HandleCollision(player, map);
	HandleCoinPickup(player, gState);
	HandleGemPickup(player, gState);
	// Death if player falls off level
	if (player.GetPosition().y > DISPLAY_HEIGHT)
	{
		PlayFallScream();
		player.SetDead(true);
		player.SetLives(player.GetLives() - 1);
		player.SetDeathTime(gState.time);
	}
}

void FallState::Enter(Player& player) const
{
	switch (m_direction)
	{
	case RIGHT:
		player.SetDrawState(State::STATE_FALL_RIGHT);
		break;
	case LEFT:
		player.SetDrawState(State::STATE_FALL_LEFT);
		break;
	}
	player.SetCrouching(false);
}

void FallState::HandleCollision(Player& player, const std::vector<GameObject*>& map) const
{
	// Rebound if colliding with level edges
	if (player.GetPosition().x > LEVEL_WIDTH - player.GetWidth())
	{
		player.SetPosition({ LEVEL_WIDTH - player.GetWidth(), player.GetPosition().y });
	}
	else if (player.GetPosition().x < 0)
	{
		player.SetPosition({ 0, player.GetPosition().y });
	}

	// Rebound if colliding sideways
	for (GameObject* p : map)
	{
		int collisionDirection = DetectCollision(&player, p, player.IsCrouching());
		if (collisionDirection == RIGHT && p->IsCollidable())
		{
			player.SetVelocity({ player.GetVelocity().x * -1, player.GetVelocity().y });
		}
	}
	// Ground player when a platform is landed on
	for (GameObject* p : map)
	{
		if (IsStandingOn(&player, p) && p->GetType() != GameObject::Type::OBJ_DECAYING_PLATFORM && p->GetType() != GameObject::Type::OBJ_DESTRUCTIBLE_PLATFORM)
		{
			player.SetGrounded(true);
		}
		else if (IsStandingOn(&player, p) && (p->GetType() == GameObject::Type::OBJ_DECAYING_PLATFORM || p->GetType() == GameObject::Type::OBJ_DESTRUCTIBLE_PLATFORM))
		{
			if (p->IsCollidable())
			{
				player.SetGrounded(true);
			}
		}
	}
}
