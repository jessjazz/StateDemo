#include "CrawlLeftState.h"
#include "CrouchLeftState.h"
#include "FallLeftState.h"
#include "RunLeftState.h"
#include "Player.h"

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

void CrawlLeftState::StateUpdate(Player& player, GameObject* p_gameObject)
{
	Point2f oldPos = player.GetPosition();
	Point2f currentPos = oldPos;

	int spriteId = Play::GetSpriteId("crawl_left_8");
	player.SetHeight(Play::GetSpriteHeight(spriteId));
	player.SetWidth(Play::GetSpriteWidth(spriteId));

	int speed = player.GetSpeed();
	player.SetVelocity({ speed / 2, 0 });
	Vector2f velocity = player.GetVelocity();

	if (player.IsColliding(player, p_gameObject))
	{
		if (player.GetPosition().y <= DISPLAY_HEIGHT - p_gameObject->GetHeight())
		{
			player.SetPosition(currentPos - velocity);
		}
		else
		{
			player.SetPosition(oldPos);
		}
	}
	else
	{
		player.SetVelocity({ 0, 0 + player.GetGravity() });
		player.SetPosition(currentPos + player.GetVelocity());
		player.SetGrounded(false);
	}
}
