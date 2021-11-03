#pragma once
#include "GameObject.h"
class Door : public GameObject
{
public:
	Door(Point2f pos);
	~Door() {}

	void Update(GameState& gState);
	void Draw(GameState& gState) const;

	static Door* CreateDoor(Point2f pos);

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

	State GetState() const { return m_state; }
	void SetState(State newState) { m_state = newState; }

private:
	int m_frame{ 0 };
	float m_framePos{ 0.0f };
	float m_animSpeed{ 0.1f };
	State m_state{ CLOSED };
};

