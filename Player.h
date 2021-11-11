#pragma once
#include "Play.h"
#include "PlayerState.h"
#include "MainGame.h"
#include "GameObject.h"

class Player : public GameObject
{
public:
	Player(Point2f pos, Vector2f gravity, int speed, int lives);
	~Player();

	void Update(GameState& gState) override;
	void Draw(GameState& gState) const override;

	static Player* CreatePlayer(Point2f pos, Vector2f gravity, int speed, int lives);
	// Sets/gets a pointer to the current PlayerState
	void SetState(PlayerState* playerState) { m_pCurrentState = playerState; }
	PlayerState* GetState() const { return m_pCurrentState; }
	// Sets the state based on the State enum in MainGame.h, used in the Player Draw function
	void SetDrawState(const State state) { m_state = state; }

	int GetSpeed() const { return m_speed; }
	void SetSpeed(const int speed) { m_speed = speed; }

	float GetAnimSpeed() const { return m_animSpeed; }
	void SetAnimSpeed(const float animSpeed) { m_animSpeed = animSpeed; }

	int GetFrame() const { return m_frame; }
	void SetFrame( const int frame) { m_frame = frame; }

	int GetLives() const { return m_lives; }
	void SetLives(const int lives) { m_lives = lives; }
	void AddLife() { m_lives++; }
	// Gets and sets the time the player died, used with respawn delay
	float GetDeathTime() const { return m_deathTime; }
	void SetDeathTime(const float time) { m_deathTime = time; }

	Vector2f GetGravity() const { return m_gravity; }
	void SetGravity(const Vector2f gravity) { m_gravity = gravity; }
	// Set b_onGround to false to enter fallState
	bool IsGrounded() const { return b_onGround; }
	void SetGrounded(const bool onGround) { b_onGround = onGround; }

	bool IsDead() const { return b_isDead; }
	void SetDead(const bool lifeState) { b_isDead = lifeState; }

	int GetCoinCount() const { return m_coinCount; }
	void AddCoinToCount(const int num) { m_coinCount += num; }
	void ResetCoinCount() { m_coinCount = 0; }

	bool IsCrouching() const { return b_isCrouching; }
	void SetCrouching(bool crouching) { b_isCrouching = crouching; }
	// Resets player to the start of the level and reduces m_lives by 1
	void HandleLifeLost(GameState& gState);

private:
	State m_state{ State::STATE_IDLE }; // This state is used for drawing sprites
	PlayerState* m_pCurrentState; // This state is the movement state for updating the player
	int m_speed;
	int m_lives;
	int m_coinCount{ 0 };
	Vector2f m_gravity;
	bool b_onGround{ false };
	bool b_isDead{ false };
	bool b_isCrouching{ false };
	int m_frame{ 0 };
	float m_framePos{ 0.0f };
	float m_animSpeed{ 0.0f };
	float m_deathTime{ 0.0f };
	// Moves the player off screen and resets coins count
	void HandleNewLevel(GameState& gState, GameObject* player);
};
