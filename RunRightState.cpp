#include "CrawlRightState.h"
#include "DashRightState.h"
#include "IdleState.h"
#include "JumpingState.h"
#include "RunRightState.h"
#include "Player.h"

constexpr int DISPLAY_HEIGHT = 720;

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
		player.SetDrawState(State::STATE_CRAWL_RIGHT);
		return new CrawlRightState;
	}

	if (Play::KeyPressed(VK_SPACE))
	{
		player.SetDrawState(State::STATE_JUMP);
		return new JumpingState;
	}

	return nullptr;
}

void RunRightState::StateUpdate(Player& player)
{
	Point2f currentPos = player.GetPosition();

	if (player.GetPosition().y <= 650)
	{
		player.SetPosition({ currentPos.x, DISPLAY_HEIGHT - 90 });
	}
	
	int speed = player.GetSpeed();

	player.SetPosition({ player.GetPosition().x + speed, player.GetPosition().y });
}
