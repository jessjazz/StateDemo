#pragma once
#include "Play.h"
#include "PlayerState.h"
#include "MainGame.h"
#include "GameObject.h"

class Player : public GameObject
{
public:
	Player(Point2f pos);
	~Player();

	void Update(GameState& gState) override;
	void Draw(GameState& gState) const override;
	void SetState(PlayerState* playerState);
	void SetDrawState(State state);
	PlayerState* GetState() const;
	int GetSpeed() const;

private:
	State m_state;
	PlayerState* m_pCurrentState;

	int m_speed;
};
