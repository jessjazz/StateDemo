#include "MainGame.h"
#include "GameObject.h"
#include "Platform.h"
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
	CreateMap(gState, 10);
	LoadSprites(gState.sprites);
	gState.player = new Player({ DISPLAY_WIDTH / 2, DISPLAY_HEIGHT - 140 });
}

bool MainGameUpdate(float elapsedTime)
{
	gState.time += elapsedTime;

	Play::DrawBackground();

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
	PlatformArgs platform7{ { 440, 420 }, 400, 50 };
	PlatformArgs platform8{ { 390, 180 }, 300, 50 };
	PlatformArgs platform9{ { 840, 180 }, 100, 50 };
	PlatformArgs platform10{ { 1080, 180 }, 200, 50 };

	PlatformArgs Platforms [10] = { platform1, platform2, platform3, platform5, platform6, 
									platform7, platform8, platform9, platform10 };

	for (int i = 0; i < platformNum; i++)
	{
		gState.s_vMap.push_back(new Platform(Platforms[i].pos, Platforms[i].width, Platforms[i].height));
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
}
