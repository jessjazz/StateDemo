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
        return new CrawlRightState;
    }

    if (!player.IsGrounded())
    {
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

	HandleCollision(player, map, speed, RIGHT); // override this with slide state's own collision function
    HandleCoinPickup(player, gState);
	HandleGemPickup(player, gState);
}

void SlideRightState::Enter(Player& player) const
{
	player.SetDrawState(State::STATE_SLIDE_RIGHT);
	player.SetCrouching(true);
}

PlayerState* SlideLeftState::HandleInput(Player& player)
{
    m_slideTime++;

    if (m_slideTime > MAX_SLIDE)
    {
        return new CrawlLeftState;
    }

    if (!player.IsGrounded())
    {
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

	HandleCollision(player, map, speed, LEFT);
    HandleCoinPickup(player, gState);
	HandleGemPickup(player, gState);
}

void SlideLeftState::Enter(Player& player) const
{
	player.SetDrawState(State::STATE_SLIDE_LEFT);
	player.SetCrouching(true);
}
