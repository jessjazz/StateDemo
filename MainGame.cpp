#include "MainGame.h"
#include "Coin.h"
#include "Door.h"
#include "GameObject.h"
#include "DecayingPlatform.h"
#include "DestructiblePlatform.h"
#include "MovingPlatform.h"
#include "Player.h"
#define PLAY_IMPLEMENTATION
#include "Play.h"

std::vector< GameObject* > GameState::s_vMap;
std::vector< GameObject* > GameState::s_vPickups;
GameState gState;

// The entry point for a Windows program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	Play::CreateManager( DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE );

	// Do things here that only need to be performed once at the start of your application
	Play::LoadBackground("Data\\Backgrounds\\background.png");
	LoadSprites(gState.sprites);
	CreateMap(gState);
	gState.camera = { 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT };
	gState.player = Player::CreatePlayer(gState.originalPlayerPos, GRAVITY, gState.playerSpeed, LIVES);
}

bool MainGameUpdate(float elapsedTime)
{
	gState.deltaTime = elapsedTime;
	gState.time += elapsedTime;

	Play::DrawBackground();

	MoveCamera(gState.player, gState.camera);
	GameObject::UpdateAll(gState);
	GameObject::DrawAll(gState);

	std::string lives = std::to_string(gState.player->GetLives());
	std::string coins = std::to_string(gState.player->GetCoinCount());
	if (gState.player->GetLives() > 0)
	{
		Play::CentreSpriteOrigin("64px");
		Play::DrawFontText("64px", ("Lives: " + lives), { 50, 50 });
		Play::DrawFontText("64px", ("Coins: " + coins), { DISPLAY_WIDTH - 150, 50 });
	}
	
	if (gState.player->GetLives() <= 0)
	{
		HandleGameOver(gState);
	}

	Play::PresentDrawingBuffer();
	return Play::KeyDown(VK_ESCAPE);
}

int MainGameExit(void)
{
	GameObject::DestroyAll();
	Play::DestroyManager();
	return PLAY_OK;
}

void CreateMap(GameState& gState)
{
	// Load regular platforms
	PlatformArgs platform1{ { 0, 670 }, 800, 50 };
	PlatformArgs platform2{ { 0, 620 }, 450, 50 };
	PlatformArgs platform3{ { 0, 570 }, 350, 50 };
	PlatformArgs platform4{ { 0, 520 }, 250, 50 };
	PlatformArgs platform5{ { 0, 310 }, 300, 50 };
	PlatformArgs platform6{ { 930, 579 }, 350, 50 };
	PlatformArgs platform7{ { 440, 440 }, 300, 50 };
	PlatformArgs platform8{ { 390, 180 }, 300, 50 };
	PlatformArgs platform9{ { 1080, 180 }, 200, 50 };
	PlatformArgs platform10{ { 3200, 400 }, 700, (DISPLAY_HEIGHT - 400) };
	PlatformArgs platform11{ { 3400, 0 }, 100, 345 };
	PlatformArgs platform12{ { 3900, 450 }, 200, (DISPLAY_HEIGHT - 450) };
	PlatformArgs platform13{ { 4100, 500 }, 150, (DISPLAY_HEIGHT - 500) };
	PlatformArgs platform14{ { 4250, 550 }, 150, (DISPLAY_HEIGHT - 550) };
	PlatformArgs platform15{ { 4400, 600 }, 150, (DISPLAY_HEIGHT - 600) };
	PlatformArgs platform16{ { 4550, 650 }, 450, 70 };

	PlatformArgs Platforms [16] = { platform1, platform2, platform3, platform5, platform6, platform7,
									platform8, platform9, platform10, platform11, platform12, platform13,
									platform14, platform15, platform16 };

	for (int i = 0; i < 16; i++)
	{
		Platform* plat = Platform::CreatePlatform(Platforms[i].pos, Platforms[i].width, Platforms[i].height);
		gState.s_vMap.push_back(plat);
	}

	// Load moving Platforms
	MovingPlatformArgs movingPlatform1{ {1390, 180}, 200, 50, VERTICAL, 4.f, 0.2f };
	MovingPlatformArgs movingPlatform2{ {1285, 180}, 100, 50, HORIZONTAL, 4.f, 0.2f };
	
	MovingPlatformArgs movingPlatforms[2] = { movingPlatform1, movingPlatform2 };

	for (int i = 0; i < 2; i++)
	{
		MovingPlatform* mPlat = MovingPlatform::CreatePlatform(movingPlatforms[i].pos, movingPlatforms[i].width, movingPlatforms[i].height, movingPlatforms[i].direction,
																movingPlatforms[i].sinAmplitude, movingPlatforms[i].sinFrequency);
		gState.s_vMap.push_back(mPlat);
	}

	// Load decaying platforms
	DecayingPlatformArgs decayingPlatform1{ {840, 180}, Play::GetSpriteWidth(gState.sprites.smallPlatform), Play::GetSpriteHeight(gState.sprites.smallPlatform), 20, 'S', 10.f, 2.f};
	DecayingPlatformArgs decayingPlatform2{ {2000, 180}, Play::GetSpriteWidth(gState.sprites.largePlatform), Play::GetSpriteHeight(gState.sprites.largePlatform), 14, 'L', 10.f, 2.f };
	DecayingPlatformArgs decayingPlatform3{ {2400, 240}, Play::GetSpriteWidth(gState.sprites.largePlatform), Play::GetSpriteHeight(gState.sprites.largePlatform), 14, 'L', 10.f, 2.f };
	DecayingPlatformArgs decayingPlatform4{ {2800, 300}, Play::GetSpriteWidth(gState.sprites.largePlatform), Play::GetSpriteHeight(gState.sprites.largePlatform), 14, 'L', 10.f, 2.f };
	
	DecayingPlatformArgs decayingPlatforms[4] = { decayingPlatform1, decayingPlatform2, decayingPlatform3, decayingPlatform4 };

	for (int i = 0; i < 4; i++)
	{
		DecayingPlatform* decPlat = DecayingPlatform::CreatePlatform(decayingPlatforms[i].pos, decayingPlatforms[i].width, decayingPlatforms[i].height, decayingPlatforms[i].decaySpeed,
																	decayingPlatforms[i].size, decayingPlatforms[i].lifeTime, decayingPlatforms[i].respawnDelay);
		gState.s_vMap.push_back(decPlat);
	}

	// Load destructible platforms
	DestructiblePlatformArgs destructiblePlatform1{ {3700, 300}, Play::GetSpriteWidth(gState.sprites.detructiblePlatform), Play::GetSpriteHeight(gState.sprites.detructiblePlatform), 10.f, 20.f };

	DestructiblePlatformArgs destructiblePlatforms[1] = { destructiblePlatform1 };

	for (int i = 0; i < 1; i++)
	{
		DestructiblePlatform* desPlat = DestructiblePlatform::CreatePlatform(destructiblePlatforms[i].pos, destructiblePlatforms[i].width, destructiblePlatforms[i].height, 
																			destructiblePlatforms[i].lifeTime, destructiblePlatforms[i].fadeSpeed);
		gState.s_vMap.push_back(desPlat);
	}

	// Put a door at the end of the level
	Door* door = Door::CreateDoor({ LEVEL_WIDTH - 100, 650 - Play::GetSpriteHeight(gState.sprites.door) });
	gState.s_vMap.push_back(door);

	CreatePickups(gState);
}

void CreatePickups(GameState& gState)
{
	PickupArgs coin1{ {1000, 530} };
	PickupArgs coin2{ {1100, 530} };
	PickupArgs coin3{ {1200, 530} };
	PickupArgs coin4{ {470, 390} };
	PickupArgs coin5{ {570, 390} };
	PickupArgs coin6{ {670, 390} };
	PickupArgs coin7{ {50, 260} };
	PickupArgs coin8{ {150, 260} };
	PickupArgs coin9{ {250, 260} };
	PickupArgs coin10 { {420, 130} };
	PickupArgs coin11{ {520, 130} };
	PickupArgs coin12{ {620, 130} };
	PickupArgs coin13{ {780, 80} };
	PickupArgs coin14{ {880, 65} };
	PickupArgs coin15{ {980, 80} };
	PickupArgs coin16{ {1120, 130} };
	PickupArgs coin17{ {1220, 130} };
	PickupArgs coin18{ {2050, 130} };
	PickupArgs coin19{ {2150, 130} };
	PickupArgs coin20{ {2250, 130} };
	PickupArgs coin21{ {2450, 190} };
	PickupArgs coin22{ {2550, 190} };
	PickupArgs coin23{ {2650, 190} };
	PickupArgs coin24{ {2850, 250} };
	PickupArgs coin25{ {2950, 250} };
	PickupArgs coin26{ {3050, 250} };

	PickupArgs coins[26] = { coin1, coin2, coin3, coin4, coin5, coin6, coin7, coin8, coin9, coin10, coin11, coin12, coin13, coin14,
							coin15, coin16, coin17, coin18, coin19, coin20, coin21, coin22, coin23, coin24, coin25, coin26 };

	for (int i = 0; i < 26; i++)
	{
		Coin* coin = Coin::CreateCoin(coins[i].pos);
		gState.s_vPickups.push_back(coin);
	}
}

void HandleGameOver(GameState& gState)
{
	Play::CentreSpriteOrigin("151px");
	Play::CentreSpriteOrigin("64px");
	Play::DrawFontText("151px", "Game Over", { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2 }, Play::CENTRE);
	Play::DrawFontText("64px", "Press enter to play again!", { DISPLAY_WIDTH / 2, 510 }, Play::CENTRE);

	if (Play::KeyPressed(VK_RETURN))
	{
		gState.player->HandleLifeLost(gState);
		gState.player->SetLives(LIVES);
		for (GameObject* item : gState.s_vPickups)
		{
			item->SetCollidable(true);
		}
	}
}

void MoveCamera(GameObject* player, CameraRect& cam)
{
	cam.x = (player->GetPosition().x + player->GetWidth() / 2.f) - DISPLAY_WIDTH / 2.f;
	cam.y = (player->GetPosition().y + player->GetHeight() / 2.f) - DISPLAY_HEIGHT / 2.f;

	if (cam.x < 0)
	{
		cam.x = 0;
	}
	if (cam.y < 0)
	{
		cam.y = 0;
	}
	if (cam.x > LEVEL_WIDTH - cam.width)
	{
		cam.x = LEVEL_WIDTH - cam.width;
	}
	if (cam.y > LEVEL_HEIGHT - cam.height)
	{
		cam.y = LEVEL_HEIGHT - cam.height;
	}
}

void LoadSprites(Sprites& sprites)
{
	sprites.idleRight = Play::GetSpriteId("idle_right");
	sprites.idleLeft = Play::GetSpriteId("idle_left");
	sprites.runRight = Play::GetSpriteId("run_right");
	sprites.runLeft = Play::GetSpriteId("run_left");
	sprites.jumpRight = Play::GetSpriteId("jump_right");
	sprites.jumpLeft = Play::GetSpriteId("jump_left");
	sprites.crouchRight = Play::GetSpriteId("crouch_right");
	sprites.crouchLeft = Play::GetSpriteId("crouch_left");
	sprites.dashRight = Play::GetSpriteId("dash_right");
	sprites.dashLeft = Play::GetSpriteId("dash_left");
	sprites.crawlRight = Play::GetSpriteId("crawl_right");
	sprites.crawlLeft = Play::GetSpriteId("crawl_left");
	sprites.slideRight = Play::GetSpriteId("slide_right");
	sprites.slideLeft = Play::GetSpriteId("slide_left");
	sprites.fallRight = Play::GetSpriteId("fall_right");
	sprites.fallLeft = Play::GetSpriteId("fall_left");
	sprites.groundPoundRight = Play::GetSpriteId("pound_right");
	sprites.groundPoundLeft = Play::GetSpriteId("pound_left");
	sprites.smallPlatform = Play::GetSpriteId("platform_100w50h");
	sprites.largePlatform = Play::GetSpriteId("platform_300");
	sprites.detructiblePlatform = Play::GetSpriteId("platform_100w100h_1");
	sprites.brokenPlatform = Play::GetSpriteId("platform_100w100h_3");
	sprites.coin = Play::GetSpriteId("coins");
	sprites.gem = Play::GetSpriteId("gem");
	sprites.door = Play::GetSpriteId("door");
}

bool IsStandingOn(GameObject* object1, GameObject* object2)
{
	PLAY_ASSERT_MSG(object1, "object1 cannot be null");
	PLAY_ASSERT_MSG(object2, "object2 cannot be null");

	float xoffset = 5.f;
	float vert_dist = 20.f;

	float object1_x1 = object1->GetPosition().x - xoffset;
	float object1_y1 = object1->GetPosition().y + object1->GetHeight();
	float object1_x2 = object1->GetPosition().x + object1->GetWidth() + xoffset;
	float object1_y2 = object1->GetPosition().y + object1->GetHeight() + vert_dist;

	float object2_x1 = object2->GetPosition().x;
	float object2_y1 = object2->GetPosition().y;
	float object2_x2 = object2->GetPosition().x + object2->GetWidth();
	float object2_y2 = object2->GetPosition().y + vert_dist;

	// Check collision below player (object1)
	if (object1_x1 < object2_x2 &&
		object1_x2 > object2_x1 &&
		object1_y1 < object2_y2 &&
		object1_y2 > object2_y1)
	{
		return true;
	}

	return false;
}

int DetectCollision(GameObject* object1, GameObject* object2, bool isCrouching)
{
	PLAY_ASSERT_MSG(object1, "object1 cannot be null");
	PLAY_ASSERT_MSG(object2, "object2 cannot be null");

	float offset = 4.f;

	float object1_y = (isCrouching) ? object1->GetPosition().y + (object1->GetHeight() / 2.f) : object1->GetPosition().y;
	float object2_y = object2->GetPosition().y;
	float object1_x = object1->GetPosition().x;
	float object2_x = object2->GetPosition().x;
	float object1_yh = object1->GetPosition().y + object1->GetHeight();
	float object2_yh = object2->GetPosition().y + object2->GetHeight();
	float object1_xw = object1->GetPosition().x + object1->GetWidth();
	float object2_xw = object2->GetPosition().x + object2->GetWidth() - offset;

	float object1_y_offset = (isCrouching) ? object1->GetPosition().y + (object1->GetHeight() / 2.f) : object1->GetPosition().y;
	float object2_yh_offset = object2->GetPosition().y + object2->GetHeight() - offset;

	float object1_x_offset = object1->GetPosition().x - offset;
	float object2_xw_offset = object2->GetPosition().x + object2->GetWidth() + offset;

	float object1_xw_offset = object1->GetPosition().x + object1->GetWidth() + offset;
	float object2_x_offset = object2->GetPosition().x - offset;

	// Check for collision above player (object1)
	if (object1_x < object2_xw &&
		object1_xw > object2_x &&
		object1_y < object2_yh &&
		object1_y_offset > object2_yh_offset)
	{
		return UP;
	}
	// Check for collision to the left of player
	else if (object1_x_offset < object2_xw_offset &&
		object1_x > object2_xw &&
		object1_y < object2_yh &&
		object1_yh > object2_y)
	{
		return LEFT;
	}
	// Check for collision to right of player
	else if (object1_xw < object2_x &&
		object1_xw_offset > object2_x_offset &&
		object1_y < object2_yh &&
		object1_yh > object2_y)
	{
		return RIGHT;
	}
	else
	{
		return 2;
	}
}
