#include "Play.h"
#pragma once

class Player;

enum State
{
	STATE_IDLE = 0,
	STATE_RUN_RIGHT,
	STATE_RUN_LEFT,
	STATE_JUMP,
	STATE_CROUCH,
	STATE_DASH_RIGHT,
	STATE_DASH_LEFT,
	STATE_INVALID = -1,
};

struct GameState
{
	float time{ 0.f };
	Player* player;
	State playerState{ STATE_IDLE };
};