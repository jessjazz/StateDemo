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
	void SetDrawState(const State state) { m_state = state; }
	
	int GetSpeed() const { return m_speed; }
	void SetSpeed(const int speed) { m_speed = speed; }

	int GetLives() const { return m_lives; }
	void SetLives(const int lives) { m_lives = lives; }

	Vector2f GetGravity() const { return m_gravity; }
	void SetGravity(const Vector2f gravity) { m_gravity = gravity; }

	bool IsGrounded() const { return b_onGround; }
	void SetGrounded(const bool onGround) { b_onGround = onGround; }

	bool IsDead() const { return b_isDead; }
	void SetDead(const bool lifeState) { b_isDead = lifeState; }

	bool IsStandingOn(const GameObject* object1, const GameObject* object2) const;
	int DetectCollision(GameObject* object1, GameObject* object2) const;

private:
	State m_state;
	PlayerState* m_pCurrentState;
	int m_speed;
	Vector2f m_gravity;
	bool b_onGround;
	bool b_isDead;
	int m_lives;

	void HandleGameOver();
	void HandleLifeLost();
};
