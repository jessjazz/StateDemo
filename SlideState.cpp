#include "SlideState.h"
#include "CrawlState.h"
#include "FallState.h"
#include "Player.h"

constexpr float MAX_SLIDE = 20.0f;

PlayerState* SlideState::HandleInput(Player& player)
{
    m_slideTime++;

    switch (m_direction)
    {
    case RIGHT:
        if (m_slideTime > MAX_SLIDE)
        {
            return new CrawlState(RIGHT);
        }

        if (!player.IsGrounded())
        {
            return new FallState(RIGHT);
        }

        return nullptr;
        break;
    
    case LEFT:
        if (m_slideTime > MAX_SLIDE)
        {
            return new CrawlState(LEFT);
        }

        if (!player.IsGrounded())
        {
            return new FallState(LEFT);
        }

        return nullptr;

    default:
        return nullptr;
        break;
    }
}

void SlideState::StateUpdate(Player& player, const std::vector<GameObject*>& map, GameState& gState) const
{
    int spriteId;
    int speed = player.GetSpeed();

    switch (m_direction)
    {
    case RIGHT:
        // Set sprite dimensions
        spriteId = gState.sprites.slideRight;
        player.SetHeight(Play::GetSpriteHeight(spriteId));
        player.SetWidth(Play::GetSpriteWidth(spriteId));
	    HandleCollision(player, map, speed, RIGHT);
        break;
    case LEFT:
        // Set sprite dimensions
        int spriteId = gState.sprites.slideLeft;
        player.SetHeight(Play::GetSpriteHeight(spriteId));
        player.SetWidth(Play::GetSpriteWidth(spriteId));
        HandleCollision(player, map, speed, LEFT);
        break;
    }
    HandleCoinPickup(player, gState);
	HandleGemPickup(player, gState);
}

void SlideState::Enter(Player& player) const
{
    switch (m_direction)
    {
    case RIGHT:
	    player.SetDrawState(State::STATE_SLIDE_RIGHT);
        break;
    case LEFT:
        player.SetDrawState(State::STATE_SLIDE_LEFT);
        break;
    }
	player.SetCrouching(true);
}