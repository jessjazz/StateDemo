#include "CrawlState.h"
#include "CrouchingState.h"
#include "FallState.h"
#include "RunningState.h"
#include "Player.h"

PlayerState* CrawlRightState::HandleInput(Player& player)
{
	if (!Play::KeyDown(VK_RIGHT))
	{
		player.SetDrawState(State::STATE_CROUCH);
		return new CrouchRightState;
	}

	if (!Play::KeyDown(VK_DOWN))
	{
		player.SetDrawState(State::STATE_RUN_RIGHT);
		return new RunRightState;
	}

	if (!player.IsGrounded())
	{
		player.SetDrawState(State::STATE_FALL_RIGHT);
		return new FallRightState;
	}

	return nullptr;
}

void CrawlRightState::StateUpdate(Player& player, std::vector<GameObject*> map)
{
	Point2f oldPos = player.GetPosition();
	Point2f currentPos = oldPos;
	
	int spriteId = Play::GetSpriteId("crawl_right_8");
	player.SetHeight(Play::GetSpriteHeight(spriteId));
	player.SetWidth(Play::GetSpriteWidth(spriteId));

	int speed = player.GetSpeed();
	player.SetVelocity({ speed / 2, 0 });
	Vector2f velocity = player.GetVelocity();

	for (GameObject* p : map)
	{
		if (player.IsColliding(player, p))
		{
			if (player.GetPosition().y <= DISPLAY_HEIGHT - p->GetHeight())
			{
				player.SetPosition(currentPos + velocity);
			}
			else
			{
				player.SetPosition(oldPos);
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

PlayerState* CrawlLeftState::HandleInput(Player& player)
{
	if (!Play::KeyDown(VK_LEFT))
	{
		player.SetDrawState(State::STATE_CROUCH_LEFT);
		return new CrouchLeftState;
	}

	if (!Play::KeyDown(VK_DOWN))
	{
		player.SetDrawState(State::STATE_RUN_LEFT);
		return new RunLeftState;
	}

	if (!player.IsGrounded())
	{
		player.SetDrawState(State::STATE_FALL_LEFT);
		return new FallLeftState;
	}

	return nullptr;
}

void CrawlLeftState::StateUpdate(Player& player, std::vector<GameObject*> map)
{
	Point2f oldPos = player.GetPosition();
	Point2f currentPos = oldPos;

	int spriteId = Play::GetSpriteId("crawl_left_8");
	player.SetHeight(Play::GetSpriteHeight(spriteId));
	player.SetWidth(Play::GetSpriteWidth(spriteId));

	int speed = player.GetSpeed();
	player.SetVelocity({ speed / 2, 0 });
	Vector2f velocity = player.GetVelocity();

	for (GameObject* p : map)
	{
		if (player.IsColliding(player, p))
		{
			if (player.GetPosition().y <= DISPLAY_HEIGHT - p->GetHeight())
			{
				player.SetPosition(currentPos - velocity);
			}
			else
			{
				player.SetPosition(oldPos);
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