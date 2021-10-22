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
    int spriteId = gState.sprites.slideRight;
    player.SetHeight(Play::GetSpriteHeight(spriteId));
    player.SetWidth(Play::GetSpriteWidth(spriteId));

    int speed = player.GetSpeed();

    HandleCollision(player, map, speed, RIGHT);
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
    int spriteId = gState.sprites.slideLeft;
    player.SetHeight(Play::GetSpriteHeight(spriteId));
    player.SetWidth(Play::GetSpriteWidth(spriteId));

    int speed = player.GetSpeed();

    HandleCollision(player, map, speed, LEFT);
}