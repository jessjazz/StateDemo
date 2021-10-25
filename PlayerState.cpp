#include "PlayerState.h"
#include "Player.h"

void PlayerState::HandleCollision(Player& player, const std::vector<GameObject*>& map, 
								const int speed, const int direction) const
{
	Point2f oldPos = player.GetPosition();
	Point2f currentPos = oldPos;

	for (GameObject* p : map)
	{
		if (player.IsStandingOn(&player, p))
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

	for (GameObject* p : map)
	{
		int collisionDirection = player.DetectCollision(&player, p);
		if (collisionDirection == -1 || collisionDirection == 2)
		{
			player.SetPosition(oldPos);
		}
	}
}
