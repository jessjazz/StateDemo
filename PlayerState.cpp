#include "PlayerState.h"
#include "Player.h"

void PlayerState::HandleCollision(Player& player, const std::vector<GameObject*>& map, 
								const int speed, const int direction) const
{
	Point2f currentPos = player.GetPosition();


	for (GameObject* p : map)
	{
		if (player.IsStandingOn(&player, p))
		{
			player.SetVelocity({ speed, 0 });

			switch (direction)
			{
			case RIGHT:
				player.SetPosition({ currentPos.x + player.GetVelocity().x, p->GetPosition().y - player.GetHeight() });
				break;
			case LEFT:
				player.SetPosition({ currentPos.x - player.GetVelocity().x, p->GetPosition().y - player.GetHeight() });
				break;
			default:
				break;
			}

			player.SetGrounded(true);
			break;
		}
		else
		{
  			player.SetVelocity({ 0, 0 + player.GetGravity() });
			player.SetPosition(currentPos + player.GetVelocity());
			player.SetGrounded(false);
		}
	}
}
