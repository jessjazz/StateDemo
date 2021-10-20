#include "FallState.h"
#include "JumpingState.h"
#include "Player.h"

constexpr float MAX_JUMP_TIME = 10.0f;
constexpr int LANDING_POS = 600;
constexpr int JUMP_HEIGHT = 10;
constexpr int JUMP_DISTANCE = 5;

PlayerState* JumpRightState::HandleInput(Player& player)
{
	m_jumpTime++;
	
	if (!Play::KeyDown(VK_SPACE) || m_jumpTime > MAX_JUMP_TIME)
	{
		player.SetDrawState(State::STATE_FALL_RIGHT);
		return new FallRightState;
	}

	return nullptr;
}

void JumpRightState::StateUpdate(Player& player, std::vector<GameObject*> map)
{
	int spriteId = Play::GetSpriteId("jump_right");
	player.SetHeight(Play::GetSpriteHeight(spriteId));
	player.SetWidth(Play::GetSpriteWidth(spriteId));

	Point2f oldPos = player.GetPosition();
	Point2f currentPos = oldPos;

	if (player.IsGrounded())
	{
		player.SetVelocity({ 0, player.GetVelocity().y - JUMP_HEIGHT });
	}
	
	if (!player.IsGrounded() && Play::KeyDown(VK_RIGHT))
	{
		player.SetVelocity({ JUMP_DISTANCE, player.GetVelocity().y });
	}
	 
	player.SetPosition(currentPos + player.GetVelocity());

	player.SetGrounded(false);
}

PlayerState* JumpLeftState::HandleInput(Player& player)
{
	m_jumpTime++;

	if (!Play::KeyDown(VK_SPACE) || m_jumpTime > MAX_JUMP_TIME)
	{
		player.SetDrawState(State::STATE_FALL_LEFT);
		return new FallLeftState;
	}

	return nullptr;
}

void JumpLeftState::StateUpdate(Player& player, std::vector<GameObject*> map)
{
	int spriteId = Play::GetSpriteId("jump_left");
	player.SetHeight(Play::GetSpriteHeight(spriteId));
	player.SetWidth(Play::GetSpriteWidth(spriteId));

	Point2f oldPos = player.GetPosition();
	Point2f currentPos = oldPos;

	if (player.IsGrounded())
	{
		player.SetVelocity({ 0, player.GetVelocity().y - JUMP_HEIGHT });
	}

	if (!player.IsGrounded() && Play::KeyDown(VK_LEFT))
	{
		player.SetVelocity({ -JUMP_DISTANCE, player.GetVelocity().y });
	}

	player.SetPosition(currentPos + player.GetVelocity());

	player.SetGrounded(false);
}