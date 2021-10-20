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
	CreateMap(gState);
	gState.player = new Player({ DISPLAY_WIDTH / 2, DISPLAY_HEIGHT - 140});
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

void CreateMap(GameState& gState)
{
	gState.s_vMap.push_back(new Platform({ 0, DISPLAY_HEIGHT - 50 }, 800, 50));
	gState.s_vMap.push_back(new Platform({ 0, DISPLAY_HEIGHT - 100 }, 450, 50));
	gState.s_vMap.push_back(new Platform({ 0, DISPLAY_HEIGHT - 150 }, 350, 50));
	gState.s_vMap.push_back(new Platform({ 0, DISPLAY_HEIGHT - 200 }, 250, 50));
	gState.s_vMap.push_back(new Platform({ 0, DISPLAY_HEIGHT / 2 - 50 }, 300, 50));
	gState.s_vMap.push_back(new Platform({ DISPLAY_WIDTH - 350, DISPLAY_HEIGHT - 150 }, 350, 50));
	gState.s_vMap.push_back(new Platform({ DISPLAY_WIDTH / 2 - 200, DISPLAY_HEIGHT / 2 + 60 }, 400, 50));
	gState.s_vMap.push_back(new Platform({ DISPLAY_WIDTH / 2 - 250, DISPLAY_HEIGHT / 4 }, 300, 50));
	gState.s_vMap.push_back(new Platform({ DISPLAY_WIDTH / 2 + 200, DISPLAY_HEIGHT / 4 }, 100, 50));
	gState.s_vMap.push_back(new Platform({ DISPLAY_WIDTH - 200, DISPLAY_HEIGHT / 4 }, 200, 50));
}
