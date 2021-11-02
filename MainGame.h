#include "Play.h"
#pragma once

class Player;
class Platform;
class GameObject;

constexpr int DISPLAY_WIDTH = 1280;
constexpr int DISPLAY_HEIGHT = 720;
constexpr int DISPLAY_SCALE = 1;

constexpr int LEVEL_WIDTH = 5000;
constexpr int LEVEL_HEIGHT = 720;

constexpr int RIGHT = 1;
constexpr int LEFT = -1;
constexpr int UP = 0;

constexpr int HORIZONTAL = 1;
constexpr int VERTICAL = 0;

constexpr int LIVES{ 3 };
const Vector2f GRAVITY{ 0, 1.5f };

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
	STATE_SMASH_RIGHT,
	STATE_SMASH_LEFT,
	STATE_INVALID = -1,
};

struct CameraRect
{
	float x;
	float y;
	float width;
	float height;
};

struct Sprites
{
	int idleRight, idleLeft, runRight, runLeft, jumpRight, jumpLeft, crouchRight, crouchLeft,
		dashRight, dashLeft, crawlRight, crawlLeft, slideRight, slideLeft, fallRight, fallLeft, 
		groundPoundRight, groundPoundLeft, smallPlatform, largePlatform, detructiblePlatform, 
		brokenPlatform, coin, gem, door;
};

struct GameState
{
	float deltaTime;
	float time{ 0.f };
	Player* player;
	Point2f originalPlayerPos{ 40, 488 };
	int playerSpeed{ 5 };
	static std::vector< GameObject* > s_vMap;
	static std::vector< GameObject* > s_vPickups;
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

struct MovingPlatformArgs
{
	Point2f pos;
	int width;
	int height;
	int direction;
	float sinAmplitude;
	float sinFrequency;
};

struct DecayingPlatformArgs
{
	Point2f pos;
	int width;
	int height;
	int decaySpeed;
	char size;
	float lifeTime;
	float respawnDelay;
};

struct DestructiblePlatformArgs
{
	Point2f pos;
	int width;
	int height;
	float lifeTime;
	float fadeSpeed;
};

struct PickupArgs
{
	Point2f pos;
};

void CreateMap(GameState& gState);

void LoadSprites(Sprites& sprites);

void CreatePickups(GameState& gState);

void MoveCamera(GameObject* player, CameraRect& cam);

bool IsStandingOn(GameObject* object1, GameObject* object2);
int DetectCollision(GameObject* object1, GameObject* object2);