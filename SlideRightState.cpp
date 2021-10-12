#include "SlideRightState.h"
#include "CrawlRightState.h"
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

    return nullptr;
}

void SlideRightState::StateUpdate(Player& player)
{
    int speed = player.GetSpeed();

    player.SetPosition({ player.GetPosition().x + speed, player.GetPosition().y });
}
