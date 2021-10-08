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
int WINAPI WinMain(PLAY_WINARGS_IN)
{
	PlayBuffer& buff = PlayBuffer::Instance(DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE, 0);
	PlayBlitter& blit = PlayBlitter::Instance("Data\\Sprites\\");
	PlaySpeaker& speak = PlaySpeaker::Instance("Data\\Sounds\\");

	// Do things here that only need to be performed once at the start of your application
	blit.SetDisplayBuffer(buff.GetDisplayBuffer(), DISPLAY_WIDTH, DISPLAY_HEIGHT);
	blit.LoadBackground("Data\\Backgrounds\\background.png");
	blit.CentreAllSpriteOrigins();
	gState.player = new Player({ DISPLAY_WIDTH / 2, DISPLAY_HEIGHT - 90 });

	return buff.HandleWindows(PLAY_WINARGS_OUT, L"State Demo");
}

bool MainGameUpdate(float elapsedTime)
{
	PlayBuffer& buff = PlayBuffer::Instance();
	PlayBlitter& blit = PlayBlitter::Instance();

	gState.time += elapsedTime;

	blit.DrawBackground();

	GameObject::UpdateAll(gState);
	GameObject::DrawAll(gState);

	buff.Present();
	return buff.KeyDown(VK_ESCAPE);
}

void MainGameExit(void)
{
	GameObject::DestroyAll();
	PlayBuffer::Destroy();
	PlayBlitter::Destroy();
	PlaySpeaker::Destroy();
}