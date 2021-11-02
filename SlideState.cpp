#include "SlideState.h"
#include "CrawlState.h"
#include "FallState.h"
#include "Player.h"

constexpr float MAX_SLIDE = 20.0f;

PlayerState* SlideRightState::HandleInput(Player& player)
{
    m_slideTime++;

    if (m_slideTime > MAX_SLIDE)
    {
        player.SetDrawState(State::STATE_CRAWL_RIGHT);
        return new CrawlRightState;
    }

    if (!player.IsGrounded())
    {
        player.SetDrawState(State::STATE_FALL_RIGHT);
        return new FallRightState;
    }

    return nullptr;
}

void SlideRightState::StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const
{
    // Set sprite dimensions
    int spriteId = gState.sprites.slideRight;
    player.SetHeight(Play::GetSpriteHeight(spriteId));
    player.SetWidth(Play::GetSpriteWidth(spriteId));

    int speed = player.GetSpeed();

	SlideRightState::HandleCollision(player, map, speed, RIGHT); // override this with slide state's own collision function
    HandleCoinPickup(player, gState);
	HandleGemPickup(player, gState);
}

void SlideRightState::HandleCollision(Player& player, const std::vector<GameObject*>& map, const int speed, const int direction) const
{
	Point2f oldPos = player.GetPosition();
	Point2f currentPos = oldPos;

	for (GameObject* p : map)
	{
		if (IsStandingOn(&player, p))
		{
			if (p->GetType() != GameObject::Type::OBJ_DECAYING_PLATFORM)
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
		if (SlideRightState::DetectCollision(&player, p) == LEFT && direction == LEFT)
		{
			player.SetPosition(oldPos);
		}
		else if (SlideRightState::DetectCollision(&player, p) == RIGHT && direction == RIGHT)
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

int SlideRightState::DetectCollision(GameObject* object1, GameObject* object2) const
{
	PLAY_ASSERT_MSG(object1, "object1 cannot be null");
	PLAY_ASSERT_MSG(object2, "object2 cannot be null");

	float offset = 3.f;

	float object1_y = object1->GetPosition().y + (object1->GetHeight() / 2.f);
	float object2_y = object2->GetPosition().y;
	float object1_x = object1->GetPosition().x;
	float object2_x = object2->GetPosition().x;
	float object1_yh = object1->GetPosition().y + object1->GetHeight();
	float object2_yh = object2->GetPosition().y + object2->GetHeight();
	float object1_xw = object1->GetPosition().x + object1->GetWidth();
	float object2_xw = object2->GetPosition().x + object2->GetWidth() - offset;

	float object1_y_offset = object1->GetPosition().y + (object1->GetHeight() / 2.f) + offset;
	float object2_yh_offset = object2->GetPosition().y + object2->GetHeight() - offset;

	float object1_x_offset = object1->GetPosition().x - offset;
	float object2_xw_offset = object2->GetPosition().x + object2->GetWidth() + offset;

	float object1_xw_offset = object1->GetPosition().x + object1->GetWidth() + offset;
	float object2_x_offset = object2->GetPosition().x - offset;

	// Check for collision above player (object1)
	if (object1_x < object2_xw &&
		object1_xw > object2_x &&
		object1_y < object2_yh &&
		object1_y_offset > object2_yh_offset)
	{
		return UP;
	}
	// Check for collision to the left of player
	else if (object1_x_offset < object2_xw_offset &&
		object1_x > object2_xw &&
		object1_y < object2_yh &&
		object1_yh > object2_y)
	{
		return LEFT;
	}
	// Check for collision to right of player
	else if (object1_xw < object2_x &&
		object1_xw_offset > object2_x_offset &&
		object1_y < object2_yh &&
		object1_yh > object2_y)
	{
		return RIGHT;
	}
	else
	{
		return 2;
	}
}

PlayerState* SlideLeftState::HandleInput(Player& player)
{
    m_slideTime++;

    if (m_slideTime > MAX_SLIDE)
    {
        player.SetDrawState(State::STATE_CRAWL_LEFT);
        return new CrawlLeftState;
    }

    if (!player.IsGrounded())
    {
        player.SetDrawState(State::STATE_FALL_LEFT);
        return new FallLeftState;
    }

    return nullptr;
}

void SlideLeftState::StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const
{
    // Set sprite dimensions
    int spriteId = gState.sprites.slideLeft;
    player.SetHeight(Play::GetSpriteHeight(spriteId));
    player.SetWidth(Play::GetSpriteWidth(spriteId));

    int speed = player.GetSpeed();

	SlideLeftState::HandleCollision(player, map, speed, LEFT); // override this with slide state's own collision function
    HandleCoinPickup(player, gState);
	HandleGemPickup(player, gState);
}

void SlideLeftState::HandleCollision(Player& player, const std::vector<GameObject*>& map, const int speed, const int direction) const
{
	Point2f oldPos = player.GetPosition();
	Point2f currentPos = oldPos;

	for (GameObject* p : map)
	{
		if (IsStandingOn(&player, p))
		{
			if (p->GetType() != GameObject::Type::OBJ_DECAYING_PLATFORM)
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
		if (SlideLeftState::DetectCollision(&player, p) == LEFT && direction == LEFT)
		{
			player.SetPosition(oldPos);
		}
		else if (SlideLeftState::DetectCollision(&player, p) == RIGHT && direction == RIGHT)
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

int SlideLeftState::DetectCollision(GameObject* object1, GameObject* object2) const
{
	PLAY_ASSERT_MSG(object1, "object1 cannot be null");
	PLAY_ASSERT_MSG(object2, "object2 cannot be null");

	float offset = 3.f;

	float object1_y = object1->GetPosition().y + (object1->GetHeight() / 2.f);
	float object2_y = object2->GetPosition().y;
	float object1_x = object1->GetPosition().x;
	float object2_x = object2->GetPosition().x;
	float object1_yh = object1->GetPosition().y + object1->GetHeight();
	float object2_yh = object2->GetPosition().y + object2->GetHeight();
	float object1_xw = object1->GetPosition().x + object1->GetWidth();
	float object2_xw = object2->GetPosition().x + object2->GetWidth() - offset;

	float object1_y_offset = object1->GetPosition().y + (object1->GetHeight() / 2.f) + offset;
	float object2_yh_offset = object2->GetPosition().y + object2->GetHeight() - offset;

	float object1_x_offset = object1->GetPosition().x - offset;
	float object2_xw_offset = object2->GetPosition().x + object2->GetWidth() + offset;

	float object1_xw_offset = object1->GetPosition().x + object1->GetWidth() + offset;
	float object2_x_offset = object2->GetPosition().x - offset;

	// Check for collision above player (object1)
	if (object1_x < object2_xw &&
		object1_xw > object2_x &&
		object1_y < object2_yh &&
		object1_y_offset > object2_yh_offset)
	{
		return UP;
	}
	// Check for collision to the left of player
	else if (object1_x_offset < object2_xw_offset &&
		object1_x > object2_xw &&
		object1_y < object2_yh &&
		object1_yh > object2_y)
	{
		return LEFT;
	}
	// Check for collision to right of player
	else if (object1_xw < object2_x &&
		object1_xw_offset > object2_x_offset &&
		object1_y < object2_yh &&
		object1_yh > object2_y)
	{
		return RIGHT;
	}
	else
	{
		return 2;
	}
}
