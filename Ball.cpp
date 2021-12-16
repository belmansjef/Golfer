#include "Ball.h"

Ball::Ball() : m_Id{ 0 }, m_IsSleeping{ true }, m_IsSelected{ false }, m_Size{ 0.0f }, m_Pos{ Point2f() }, m_Acceleration{ Point2f() }, m_Velocity{ Point2f() }
{
}

Ball::Ball(int id, const Point2f& pos, float size) : m_Id{ id }, m_IsSleeping{ true }, m_IsSelected{ false }, m_Size{ size }, m_Pos{ pos }, m_Acceleration{ Point2f() }, m_Velocity{ Point2f() }
{
}

bool Ball::IsPointInCircle(const Point2f& point)
{
	return utils::GetDistance(m_Pos, point) <= m_Size;
}

bool Ball::IsSelected()
{
	return m_IsSelected;
}

int Ball::GetId()
{
	return m_Id;
}

Point2f Ball::GetPosition()
{
	return m_Pos;
}

float Ball::GetSize()
{
	return m_Size;
}

void Ball::Select()
{
	m_IsSelected = true;
}

void Ball::Deselect()
{
	m_IsSelected = false;
}

void Ball::Shoot(const Point2f& mousePos)
{
	const float force{ 5.0f };
	m_Velocity.x = force * (m_Pos.x - mousePos.x);
	m_Velocity.y = force * (m_Pos.y - mousePos.y);

	m_IsSleeping = false;
}

void Ball::CheckCollision(float windowWidth, float windowHeight)
{
	if (m_Pos.x + m_Size > windowWidth || m_Pos.x - m_Size < 0.0f)
	{
		m_Velocity.x *= -1;
	}

	if (m_Pos.y + m_Size > windowHeight || m_Pos.y - m_Size < 0.0f)
	{
		m_Velocity.y *= -1;
	}
}

void Ball::Update(float deltaTime, float windowWidth, float windowHeight)
{
	if (m_IsSleeping) return;

	CheckCollision(windowWidth, windowHeight);

	const float drag{ 1.2f };
	m_Acceleration.x = -m_Velocity.x * drag;
	m_Acceleration.y = -m_Velocity.y * drag;

	m_Velocity.x += m_Acceleration.x * deltaTime;
	m_Velocity.y += m_Acceleration.y * deltaTime;
	m_Pos.x += m_Velocity.x * deltaTime;
	m_Pos.y += m_Velocity.y * deltaTime;

	if (fabsf((m_Velocity.x * m_Velocity.x) + (m_Velocity.y * m_Velocity.y)) < 0.1f)
	{
		m_Velocity.x = 0.0f;
		m_Velocity.y = 0.0f;
		m_IsSleeping = true;
	}
}

void Ball::Draw()
{
	utils::SetColor(1.0f, 1.0f, 1.0f);
	utils::FillEllipse(m_Pos, m_Size, m_Size);
}
