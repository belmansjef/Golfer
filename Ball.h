#pragma once
#include "pch.h"

class Ball
{
private:
	int m_Id{};

	bool m_IsSleeping{};
	bool m_IsSelected{};
	float m_Size{};
	float m_Force{};
	float m_MaxVelocity{};
	Point2f m_Pos{};
	Point2f m_Acceleration{};
	Point2f m_Velocity{};

public:
	// Constructor
	Ball();
	Ball(int id, const Point2f& pos, float size);

	// Methods
	bool IsPointInCircle(const Point2f& point);
	bool IsSelected();

	bool GetSleepingState();
	int GetId();
	Point2f GetPosition();
	Point2f GetVelocity();
	float GetSize();

	void SetPosition(const Point2f& pos);

	void BounceHorizontal(const Point2f& colliderCenter, float collisionOverlap);
	void BounceVertical(const Point2f& colliderCenter, float collisionOverlap);
	void Select();
	void Deselect();
	void Shoot(const Point2f& mousePos);

	void Update(float deltaTime);
	void Draw();
	void DrawNextFrame(float deltaTime);
	void DrawShotLine(const Point2f& mousePos);
};

