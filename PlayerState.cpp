#include "PlayerState.h"
#include "Player.h"

void PlayerState::HandleCollision(Player& player, const std::vector<GameObject*>& map, 
								const int speed, const int direction) const
{
	Point2f oldPos = player.GetPosition();
	Point2f currentPos = oldPos;

	for (GameObject* p : map)
	{
		if (IsStandingOn(&player, p))
		{
			if (p->GetType() != GameObject::Type::OBJ_DECAYING_PLATFORM && p->GetType() != GameObject::Type::OBJ_DESTRUCTIBLE_PLATFORM)
			{
				switch (direction)
				{
				case RIGHT:
					player.SetVelocity({ speed, 0 });
					player.SetPosition({ currentPos.x + player.GetVelocity().x, p->GetPosition().y - player.GetHeight() });
					break;
				case LEFT:
					player.SetVelocity({ -speed, 0 });
					player.SetPosition({ currentPos.x + player.GetVelocity().x, p->GetPosition().y - player.GetHeight() });
					break;
				default:
					break;
				}

				player.SetGrounded(true);
				break;
			}
			else
			{
				if (p->IsCollidable())
				{
					switch (direction)
					{
					case RIGHT:
						player.SetVelocity({ speed, 0 });
						player.SetPosition({ currentPos.x + player.GetVelocity().x, p->GetPosition().y - player.GetHeight() });
						break;
					case LEFT:
						player.SetVelocity({ -speed, 0 });
						player.SetPosition({ currentPos.x + player.GetVelocity().x, p->GetPosition().y - player.GetHeight() });
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

	for (GameObject* p : map)
	{
		if (DetectCollision(&player, p) == LEFT && direction == LEFT)
		{
			player.SetPosition(oldPos);
		}
		else if (DetectCollision(&player, p) == RIGHT && direction == RIGHT)
		{
			player.SetPosition(oldPos);
		}
	}

	if (player.GetPosition().x > LEVEL_WIDTH - player.GetWidth())
	{
		player.SetPosition({ LEVEL_WIDTH - player.GetWidth(), currentPos.y });
	}
	else if (player.GetPosition().x <= 0)
	{
		player.SetPosition({ 0, currentPos.y });
	}
}

void PlayerState::HandleCoinPickup(Player& player, GameState& gState) const
{
	for (GameObject* obj : gState.s_vPickups)
	{
		if (obj->GetType() == GameObject::Type::OBJ_COIN)
		{
			Coin* coin = static_cast<Coin*>(obj);
			if ((DetectCollision(&player, coin) == LEFT || DetectCollision(&player, coin) == RIGHT || DetectCollision(&player, coin) == UP) && coin->IsCollidable())
			{
				player.AddCoinToCount(1);
				coin->SetCollidable(false);
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
			if ((DetectCollision(&player, gem) == LEFT || DetectCollision(&player, gem) == RIGHT || DetectCollision(&player, gem) == UP) && gem->IsCollidable())
			{
				player.AddLife();
				gem->SetCollidable(false);
			}
		}
	}
}
