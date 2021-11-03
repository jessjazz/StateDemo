#include "FallState.h"
#include "Player.h"
#include "IdleState.h"

PlayerState* FallRightState::HandleInput(Player& player)
{
	if (player.IsGrounded())
	{
		return new IdleRightState;
	}
	
	return nullptr;
}

void FallRightState::StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const
{
	// Set sprite dimensions
	int spriteId = gState.sprites.fallRight;
	player.SetHeight(Play::GetSpriteHeight(spriteId));
	player.SetWidth(Play::GetSpriteWidth(spriteId));
	
	Point2f currentPos = player.GetPosition();

	player.SetVelocity(player.GetVelocity() + player.GetGravity());
	player.SetPosition(currentPos + player.GetVelocity());

	// Handle level edges
	if (player.GetPosition().x > LEVEL_WIDTH - player.GetWidth())
	{
		player.SetPosition({ LEVEL_WIDTH - player.GetWidth(), player.GetPosition().y });
	}
	else if (player.GetPosition().x < 0)
	{
		player.SetPosition({ 0, player.GetPosition().y });
	}

	// Handle sideways collision
	for (GameObject* p : map)
	{
		int collisionDirection = DetectCollision(&player, p, player.IsCrouching());
		if (collisionDirection == RIGHT && p->IsCollidable())
		{
			player.SetVelocity({ player.GetVelocity().x * -1, player.GetVelocity().y });
		}
	}
	// Handle collision from above
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

	HandleCoinPickup(player, gState);
	HandleGemPickup(player, gState);

	if (player.GetPosition().y > DISPLAY_HEIGHT)
	{
		player.SetDead(true);
		player.SetLives(player.GetLives() - 1);
	}
}

void FallRightState::Enter(Player& player) const
{
	player.SetDrawState(State::STATE_FALL_RIGHT);
	player.SetCrouching(false);
}

PlayerState* FallLeftState::HandleInput(Player& player)
{
	if (player.IsGrounded())
	{
		return new IdleLeftState;
	}
	return nullptr;
}

void FallLeftState::StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const
{
	// Set sprite dimensions
	int spriteId = gState.sprites.fallLeft;
	player.SetHeight(Play::GetSpriteHeight(spriteId));
	player.SetWidth(Play::GetSpriteWidth(spriteId));

	Point2f currentPos = player.GetPosition();

	player.SetVelocity(player.GetVelocity() + player.GetGravity());
	player.SetPosition(currentPos + player.GetVelocity());

	// Handle level edges
	if (player.GetPosition().x > LEVEL_WIDTH - player.GetWidth())
	{
		player.SetPosition({ LEVEL_WIDTH - player.GetWidth(), player.GetPosition().y });
	}
	else if (player.GetPosition().x < 0)
	{
		player.SetPosition({ 0, player.GetPosition().y });
	}

	// Handle sideways collision
	for (GameObject* p : map)
	{
		int collisionDirection = DetectCollision(&player, p, player.IsCrouching());
		if (collisionDirection == LEFT && p->IsCollidable())
		{
			player.SetVelocity({ player.GetVelocity().x * -1, player.GetVelocity().y });
		}
	}
	// Handle collision from above
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

	HandleCoinPickup(player, gState);
	HandleGemPickup(player, gState);

	if (player.GetPosition().y > DISPLAY_HEIGHT)
	{
		player.SetDead(true);
		player.SetLives(player.GetLives() - 1);
	}
}

void FallLeftState::Enter(Player& player) const
{
	player.SetDrawState(State::STATE_FALL_LEFT);
	player.SetCrouching(false);
}
