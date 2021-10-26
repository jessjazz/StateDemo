#include "MainGame.h"
#include "GameObject.h"
#include "DecayingPlatform.h"
#include "MovingPlatform.h"
#include "Player.h"
#define PLAY_IMPLEMENTATION
#include "Play.h"

std::vector< GameObject* > GameState::s_vMap;
GameState gState;

// The entry point for a Windows program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	Play::CreateManager( DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE );

	// Do things here that only need to be performed once at the start of your application
	Play::LoadBackground("Data\\Backgrounds\\background.png");
	CreateMap(gState, 9);
	LoadSprites(gState.sprites);
	gState.camera = { 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT };
	gState.player = new Player(gState.originalPlayerPos);
}

bool MainGameUpdate(float elapsedTime)
{
	gState.deltaTime = elapsedTime;
	gState.time += elapsedTime;

	Play::DrawBackground();

	std::string lives = std::to_string(gState.player->GetLives());
	if (gState.player->GetLives() > 0)
	{
		Play::CentreSpriteOrigin("64px");
		Play::DrawFontText("64px", ("Lives: " + lives), { 50, 50 });
	}

	MoveCamera(gState.player, gState.camera);
	GameObject::UpdateAll(gState);
	GameObject::DrawAll(gState);

	Play::PresentDrawingBuffer();
	return Play::KeyDown(VK_ESCAPE);
}

int MainGameExit(void)
{
	GameObject::DestroyAll();
	Play::DestroyManager();
	return PLAY_OK;
}

void CreateMap(GameState& gState, const int platformNum)
{
	PlatformArgs platform1{ { 0, 670 }, 800, 50 };
	PlatformArgs platform2{ { 0, 620 }, 450, 50 };
	PlatformArgs platform3{ { 0, 570 }, 350, 50 };
	PlatformArgs platform4{ { 0, 520 }, 250, 50 };
	PlatformArgs platform5{ { 0, 310 }, 300, 50 };
	PlatformArgs platform6{ { 930, 570 }, 350, 50 };
	PlatformArgs platform7{ { 440, 440 }, 300, 50 };
	PlatformArgs platform8{ { 390, 180 }, 300, 50 };
	PlatformArgs platform9{ { 1080, 180 }, 200, 50 };

	PlatformArgs Platforms [9] = { platform1, platform2, platform3, platform5, platform6, 
									platform7, platform8, platform9 };

	for (int i = 0; i < platformNum; i++)
	{
		gState.s_vMap.push_back(new Platform(Platforms[i].pos, Platforms[i].width, Platforms[i].height));
	}

	PlatformArgs movingPlatform1{ {1390, 180}, 200, 50 };
	PlatformArgs movingPlatform2{ {1285, 180}, 100, 50 };
	gState.s_vMap.push_back(new MovingPlatform(movingPlatform1.pos, movingPlatform1.width, movingPlatform1.height, 0));
	gState.s_vMap.push_back(new MovingPlatform(movingPlatform2.pos, movingPlatform2.width, movingPlatform2.height, 1));

	PlatformArgs decayingPlatform1{ {840, 180}, Play::GetSpriteWidth(gState.sprites.platform), Play::GetSpriteHeight(gState.sprites.platform) };
	gState.s_vMap.push_back(new DecayingPlatform(decayingPlatform1.pos, decayingPlatform1.width, decayingPlatform1.height));
}

void MoveCamera(GameObject* player, CameraRect& cam)
{
	cam.x = (player->GetPosition().x + player->GetWidth() / 2) - DISPLAY_WIDTH / 2;
	cam.y = (player->GetPosition().y + player->GetHeight() / 2) - DISPLAY_HEIGHT / 2;

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
	sprites.platform = Play::GetSpriteId("platform");
}
