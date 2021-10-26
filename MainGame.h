#include "Play.h"
#pragma once

class Player;
class Platform;
class GameObject;

constexpr int DISPLAY_WIDTH = 1280;
constexpr int DISPLAY_HEIGHT = 720;
constexpr int DISPLAY_SCALE = 1;
constexpr int LEVEL_WIDTH = 2560;
constexpr int LEVEL_HEIGHT = 720;

enum class State
{
	STATE_IDLE = 0,
	STATE_IDLE_LEFT,
	STATE_RUN_RIGHT,
	STATE_RUN_LEFT,
	STATE_JUMP,
	STATE_JUMP_LEFT,
	STATE_CROUCH,
	STATE_CROUCH_LEFT,
	STATE_DASH_RIGHT,
	STATE_DASH_LEFT,
	STATE_CRAWL_RIGHT,
	STATE_CRAWL_LEFT,
	STATE_SLIDE_RIGHT,
	STATE_SLIDE_LEFT,
	STATE_FALL_RIGHT,
	STATE_FALL_LEFT,
	STATE_INVALID = -1,
};

struct CameraRect
{
	int x;
	int y;
	int width;
	int height;
};

struct Sprites
{
	int idleRight, idleLeft, runRight, runLeft, jumpRight, jumpLeft, crouchRight, crouchLeft,
		dashRight, dashLeft, crawlRight, crawlLeft, slideRight, slideLeft, fallRight, fallLeft, platform;
};

struct GameState
{
	float deltaTime;
	float time{ 0.f };
	Player* player;
	Point2f originalPlayerPos{ 40, 488 };
	static std::vector< GameObject* > s_vMap;
	State playerState = State::STATE_IDLE;
	Sprites sprites;
	CameraRect camera;
};

struct PlatformArgs
{
	Point2f pos;
	int width;
	int height;
};

void CreateMap(GameState& gState, const int platformNum);

void LoadSprites(Sprites& sprites);

void MoveCamera(GameObject* player, CameraRect& cam);