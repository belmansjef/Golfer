#pragma once
#include "pch.h"

class Ball
{
private:
	int m_Id{};

	bool m_IsSleeping{};
	bool m_IsSelected{};
	float m_Size{};
	Point2f m_Pos{};
	Point2f m_Acceleration{};
	Point2f m_Velocity{};

	void CheckCollision(float windowWidth, float windowHeight);

public:
	// Constructor
	Ball();
	Ball(int id, const Point2f& pos, float size);

	// Methods
	bool IsPointInCircle(const Point2f& point);
	bool IsSelected();
	int GetId();
	Point2f GetPosition();
	float GetSize();
	
	void Select();
	void Deselect();
	void Shoot(const Point2f& mousePos);

	void Update(float deltaTime, float windowWidth, float windowHeight);
	void Draw();
};

