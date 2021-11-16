#pragma once
#include "GameObject.h"
class Door : public GameObject
{
public:
	Door(Point2f pos);
	~Door() {}

	void Update(GameState& gState);
	void Draw(GameState& gState) const;
	// Create function to hide raw new
	static Door* CreateDoor(Point2f pos);
	// State enum to control sprites and behaviour
	enum State
	{
		CLOSED = 0,
		OPENING,
		OPEN,
	};

	float GetAnimSpeed() const { return m_animSpeed; }
	void SetAnimSpeed(const float animSpeed) { m_animSpeed = animSpeed; }

	int GetFrame() const { return m_frame; }
	void SetFrame(const int frame) { m_frame = frame; }

	float GetFramePos() const { return m_framePos; }
	void SetFramePos(const float framePos) { m_framePos = framePos; }

	State GetState() const { return m_state; }
	void SetState(State newState) { m_state = newState; }

protected:
	int m_frame{ 0 };
	float m_framePos{ 0.0f };
	float m_animSpeed{ 0.1f };
	State m_state{ CLOSED };
};

