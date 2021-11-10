#include "PlayerState.h"
#include "Player.h"
#include "Star.h"

void PlayerState::HandleCollision(Player& player, const std::vector<GameObject*>& map, 
								const int speed, const int direction) const
{
	Point2f oldPos = player.GetPosition();
	Point2f currentPos = oldPos;
	// Checks if player is standing on a platform and sets position accordingly
	// If platform is destructible or decays, once platform is invisible, player is not grounded
	for (GameObject* platform : map)
	{
		if (IsStandingOn(&player, platform))
		{
			if (platform->GetType() != GameObject::Type::OBJ_DECAYING_PLATFORM && platform->GetType() != GameObject::Type::OBJ_DESTRUCTIBLE_PLATFORM)
			{
				switch (direction)
				{
				case RIGHT:
					player.SetVelocity({ speed, 0 });
					player.SetPosition({ currentPos.x + player.GetVelocity().x, platform->GetPosition().y - player.GetHeight() });
					break;
				case LEFT:
					player.SetVelocity({ -speed, 0 });
					player.SetPosition({ currentPos.x + player.GetVelocity().x, platform->GetPosition().y - player.GetHeight() });
					break;
				default:
					break;
				}

				player.SetGrounded(true);
				break;
			}
			else
			{
				if (platform->IsCollidable())
				{
					switch (direction)
					{
					case RIGHT:
						player.SetVelocity({ speed, 0 });
						player.SetPosition({ currentPos.x + player.GetVelocity().x, platform->GetPosition().y - player.GetHeight() });
						break;
					case LEFT:
						player.SetVelocity({ -speed, 0 });
						player.SetPosition({ currentPos.x + player.GetVelocity().x, platform->GetPosition().y - player.GetHeight() });
						break;
					default:
						break;
					}

					player.SetGrounded(true);
					break;
				}
				else
				{
					player.SetGrounded(false);
				}
			}
		}
		else
		{
			player.SetGrounded(false);
		}
	}
	// Resets position of player if colliding with a platform to their left or right
	for (GameObject* platform : map)
	{
		if ((DetectCollision(&player, platform, player.IsCrouching()) == LEFT && direction == LEFT) || 
			(DetectCollision(&player, platform, player.IsCrouching()) == RIGHT && direction == RIGHT))
		{
			if (platform->IsCollidable())
			{
				player.SetPosition(oldPos);
			}
		}
	}
	// Stops player running off the start or end of the level
	if (player.GetPosition().x > LEVEL_WIDTH - player.GetWidth())
	{
		player.SetPosition({ LEVEL_WIDTH - player.GetWidth(), currentPos.y });
	}
	else if (player.GetPosition().x <= 0)
	{
		player.SetPosition({ 0, currentPos.y });
	}
}

int PlayerState::HandleCrouchingCollision(Player& player)
{
	std::vector<GameObject*> platforms;
	GameObject::GetObjectList(GameObject::OBJ_PLATFORM, platforms);

	for (GameObject* platform : platforms)
	{
		if (DetectCollision(&player, platform, true) == UP)
		{
			hitCount++;
		}
	}

	return hitCount;
}

void PlayerState::HandleCoinPickup(Player& player, GameState& gState) const
{
	for (GameObject* obj : gState.s_vPickups)
	{
		if (obj->GetType() == GameObject::Type::OBJ_COIN)
		{
			Coin* coin = static_cast<Coin*>(obj);
			if (Coin::IsColliding(&player, coin, player.IsCrouching()) && coin->IsCollidable())
			{
				player.AddCoinToCount(1);
				coin->SetCollidable(false);
				Play::PlayAudio("collect");
				Star::SpawnStars(coin->GetPosition());
			}
		}
	}
}

void PlayerState::HandleGemPickup(Player& player, GameState& gState) const
{
	for (GameObject* obj : gState.s_vPickups)
	{
		if (obj->GetType() == GameObject::Type::OBJ_GEM)
		{
			Gem* gem = static_cast<Gem*>(obj);
			if ((DetectCollision(&player, gem, player.IsCrouching()) == LEFT || DetectCollision(&player, gem, player.IsCrouching()) == RIGHT || DetectCollision(&player, gem, player.IsCrouching()) == UP) && gem->IsCollidable())
			{
				player.AddLife();
				gem->SetCollidable(false);
				Play::PlayAudio("gem");
				Star::SpawnStars(gem->GetPosition());
			}
		}
	}
}

void PlayerState::PlayFallScream() const
{
	switch (Play::RandomRoll(3))
	{
	case 1:
		Play::PlayAudio("fall_1");
		break;
	case 2:
		Play::PlayAudio("fall_2");
		break;
	case 3:
		Play::PlayAudio("fall_3");
		break;
	}
}
