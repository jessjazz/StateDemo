#include "SlideRightState.h"
#include "DashRightState.h"
#include "FallRightState.h"
#include "IdleState.h"
#include "JumpingState.h"
#include "RunRightState.h"
#include "Player.h"

constexpr int JUMP_HEIGHT = 600;

PlayerState* RunRightState::HandleInput(Player& player)
{
	if (!Play::KeyDown(VK_RIGHT))
	{
		player.SetDrawState(State::STATE_IDLE);
		return new IdleState;
	}

	if (Play::KeyPressed(VK_SHIFT))
	{
		player.SetDrawState(State::STATE_DASH_RIGHT);
		return new DashRightState;
	}

	if (Play::KeyPressed(VK_DOWN))
	{
		player.SetDrawState(State::STATE_SLIDE_RIGHT);
		return new SlideRightState;
	}

	if (Play::KeyPressed(VK_SPACE))
	{
		player.SetDrawState(State::STATE_JUMP);
		return new JumpingState;
	}

	if (!player.IsGrounded())
	{
		player.SetDrawState(State::STATE_FALL_RIGHT);
		return new FallRightState;
	}

	return nullptr;
}

void RunRightState::StateUpdate(Player& player, std::vector<GameObject*> map)
{
	Point2f oldPos = player.GetPosition();
	Point2f currentPos = oldPos;

	int spriteId = Play::GetSpriteId("run_right_8");
	player.SetHeight(Play::GetSpriteHeight(spriteId));
	player.SetWidth(Play::GetSpriteWidth(spriteId));

	int speed = player.GetSpeed();

	for (GameObject* p : map)
	{
		if (player.IsColliding(player, p))
		{
			if (player.GetPosition().y <= DISPLAY_HEIGHT - p->GetHeight())
			{
				player.SetVelocity({ speed, 0 });
				player.SetPosition({ currentPos.x + player.GetVelocity().x, (p->GetPosition().y - player.GetHeight() + 1) });
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
