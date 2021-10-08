#pragma once
#include "Play.h"
#include "PlayerState.h"
#include "MainGame.h"
#include "GameObject.h"

class IdleState;
class JumpingState;
class CrouchingState;
class RunRightState;
class RunLeftState;

class Player : public GameObject
{
public:
	Player(Point2f pos);
	~Player();

	void Update(GameState& gState) override;
	void Draw(GameState& gState) const override;
	void SetState(State newState);
	int GetSpeed() const;

private:
	State m_state;
	State m_pendingState;
	PlayerState* m_pCurrentState;

	int m_speed;

	static IdleState s_idleState;
	static JumpingState s_jumpingState;
	static CrouchingState s_crouchingState;
	static RunRightState s_runRightState;
	static RunLeftState s_runLeftState;
};
