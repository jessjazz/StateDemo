#pragma once
#include "GameObject.h"
class Star : public GameObject
{
public:
	Star(Point2f pos);
	~Star() {}

	void Update(GameState& gState);
	void Draw(GameState& gState) const;

	static void SpawnStars(Point2f pos);

private:
	float m_rot{ 0.0f };
	float m_rotationSpeed{ 0.0f };
	Vector2f m_accelaration{ 0.0f, 0.0f };
};

