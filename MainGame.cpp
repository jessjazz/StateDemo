#include "MainGame.h"
#include "GameObject.h"
#include "Player.h"
#define PLAY_IMPLEMENTATION
#include "Play.h"

constexpr int DISPLAY_WIDTH = 1280;
constexpr int DISPLAY_HEIGHT = 720;
constexpr int DISPLAY_SCALE = 1;

GameState gState;

// The entry point for a Windows program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	Play::CreateManager( DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE );

	// Do things here that only need to be performed once at the start of your application
	Play::LoadBackground("Data\\Backgrounds\\background.png");
	Play::CentreAllSpriteOrigins();
	gState.player = new Player({ DISPLAY_WIDTH / 2, DISPLAY_HEIGHT - 90 });

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