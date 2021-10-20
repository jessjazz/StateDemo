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
        player.SetDrawState(STATE_CRAWL_RIGHT);
        return new CrawlRightState;
    }

    if (!player.IsGrounded())
    {
        player.SetDrawState(State::STATE_FALL_RIGHT);
        return new FallRightState;
    }

    return nullptr;
}

void SlideRightState::StateUpdate(Player& player, std::vector<GameObject*> map)
{
    int spriteId = Play::GetSpriteId("slide_right_4");
    player.SetHeight(Play::GetSpriteHeight(spriteId));
    player.SetWidth(Play::GetSpriteWidth(spriteId));

    Point2f oldPos = player.GetPosition();
    Point2f currentPos = oldPos;

    int speed = player.GetSpeed();
    player.SetVelocity({ speed, 0 });
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

PlayerState* SlideLeftState::HandleInput(Player& player)
{
    m_slideTime++;

    if (m_slideTime > MAX_SLIDE)
    {
        player.SetDrawState(STATE_CRAWL_LEFT);
        return new CrawlLeftState;
    }

    if (!player.IsGrounded())
    {
        player.SetDrawState(State::STATE_FALL_LEFT);
        return new FallLeftState;
    }

    return nullptr;
}

void SlideLeftState::StateUpdate(Player& player, std::vector<GameObject*> map)
{
    int spriteId = Play::GetSpriteId("slide_left_4");
    player.SetHeight(Play::GetSpriteHeight(spriteId));
    player.SetWidth(Play::GetSpriteWidth(spriteId));

    Point2f oldPos = player.GetPosition();
    Point2f currentPos = oldPos;

    int speed = player.GetSpeed();
    player.SetVelocity({ speed, 0 });
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