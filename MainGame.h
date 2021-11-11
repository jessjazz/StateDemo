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
// Direction constants for use in collision checks
constexpr int RIGHT = 1;
constexpr int LEFT = -1;
constexpr int UP = 0;
// Direction constants for use in moving platforms
constexpr int HORIZONTAL = 1;
constexpr int VERTICAL = 0;

constexpr int LIVES{ 3 };
const Vector2f GRAVITY{ 0, 1.0f };
// Player states for use in Player::Draw function
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
// Camera values
struct CameraRect
{
	float x;
	float y;
	float width;
	float height;
};
// Struct of spriteIDs that are loaded at MainGameEntry and can be accessed anywhere through GameState
struct Sprites
{
	int idleRight, idleLeft, runRight, runLeft, jumpRight, jumpLeft, crouchRight, crouchLeft,
		dashRight, dashLeft, crawlRight, crawlLeft, slideRight, slideLeft, fallRight, fallLeft, 
		groundPoundRight, groundPoundLeft, smallPlatform, largePlatform, detructiblePlatform, 
		brokenPlatform, coin, gem, door, star;
};
// Keeps track of the current state of the game
struct GameState
{
	float deltaTime{0.0f}; // Time since last frame
	float time{ 0.0f }; // Cumulative time game has been running
	Player* player; // Instance of playable character
	Point2f originalPlayerPos{ 40, 488 };
	int playerSpeed{ 5 };
	static std::vector< GameObject* > s_vMap; // Vector for storing level map data (platforms/doors)
	static std::vector< GameObject* > s_vPickups; // Vector for storing pickups (coins/gems)
	State playerState = State::STATE_IDLE; // Initial playerState when game is loaded
	Sprites sprites; // Instance of sprite struct to store spriteIDs
	CameraRect camera; // Instance of camera
	Point2f cameraTarget{ 0,0 };
	bool levelEnd{ false };
};
// Structs to store platform/pickup data to pass into create functions
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
	int direction; // Can be vertical or horizontal
	float sinAmplitude; // Change this to alter how far platform moves
	float sinFrequency; // Change this to alter how fast the platform moves
};

struct DecayingPlatformArgs
{
	Point2f pos;
	int width;
	int height;
	int decaySpeed; // Controls how fast the platform will disappear
	char size; // Used to set sprite to the large or small version, enter 'S'/'s' or 'L'/'l'
	float lifeTime; // Controls how long the platform is visible
	float respawnDelay; // Delays the platform reappearing so the player can fall through it
};

struct DestructiblePlatformArgs
{
	Point2f pos;
	int width;
	int height;
	float lifeTime; // Controls how long the broken platform pieces are visible
	float fadeSpeed; // Controls how fast the broken platform pieces will disappear
};

struct PickupArgs
{
	Point2f pos;
};
// Creates new platforms, doors and calls create pickups at game entry
void CreateMap(GameState& gState);
// Calls GetSpriteID for every sprite before the game starts
void LoadSprites(Sprites& sprites);
// Creates new coins at game entry
void CreatePickups(GameState& gState);
// Centres the camera on the player, if player is near the edge of level, clamps camera position
void MoveCamera(GameObject* player, CameraRect& cam);
// Camera getters and setters
void SetCameraPos(Point2f pos);
Point2f GetCameraPos();
// Draws HUD icons and tutorial text
void ShowHUD(GameState& gState);
// Checks if an object is directly on top of another object
bool IsStandingOn(GameObject* object1, GameObject* object2);
// Checks for collision left, right and above. Returns one of 3 values if colliding, or 0 if not
int DetectCollision(GameObject* object1, GameObject* object2, bool isCrouching);
// Shows game over screen and allows player to restart by pressing enter
void HandleGameOver(GameState& gState);
// Shows level end screen and allows player to restart by pressing enter. Resets platforms and pickups
void HandleLevelEnd(GameState& gState);
// Draws rectangle as visual representation of collision
void DrawCollisionRects(GameObject* player);
