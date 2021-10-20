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

	void SetState(PlayerState* playerState) { m_pCurrentState = playerState; }
	PlayerState* GetState() const { return m_pCurrentState; }
	void SetDrawState(State state) { m_state = state; }
	
	int GetSpeed() const { return m_speed; }
	void SetSpeed(int speed) { m_speed = speed; }

	float GetGravity() const { return m_gravity; }
	void SetGravity(float gravity) { m_gravity = gravity; }

	bool IsGrounded() const { return b_onGround; }
	void SetGrounded(bool onGround) { b_onGround = onGround; }

	bool IsDead() const { return b_isDead; }
	void SetDead(bool lifeState) { b_isDead = lifeState; }

	bool IsStandingOn(GameObject& object1, GameObject* object2);

private:
	State m_state;
	PlayerState* m_pCurrentState;
	int m_speed;
	float m_gravity;
	bool b_onGround;
	bool b_isDead;

	void HandleGameOver();
};
