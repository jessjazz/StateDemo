#include "SlideLeftState.h"
#include "CrawlLeftState.h"
#include "Player.h"

constexpr float MAX_SLIDE = 20.0f;

PlayerState* SlideLeftState::HandleInput(Player& player)
{
    m_slideTime++;

    if (m_slideTime > MAX_SLIDE)
    {
        player.SetDrawState(STATE_CRAWL_LEFT);
        return new CrawlLeftState;
    }

    return nullptr;
}

void SlideLeftState::StateUpdate(Player& player)
{
    int speed = player.GetSpeed();

    player.SetPosition({ player.GetPosition().x - speed, player.GetPosition().y });
}
