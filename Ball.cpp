#include "Ball.h"

Ball::Ball()
	: m_Id{ 0 }
	, m_IsSleeping{ true }
	, m_IsSelected{ false }
	, m_Size{ 0.0f }
	, m_Force{ 10.0f }
	, m_MaxVelocity{ 1000.0f }
	, m_Pos{ Point2f() }
	, m_Acceleration{ Point2f() }
	, m_Velocity{ Point2f() }
{
}

Ball::Ball(int id, const Point2f& pos, float size)
	: m_Id{ id }
	, m_IsSleeping{ true }
	, m_IsSelected{ false }
	, m_Size{ size }
	, m_Force{ 10.0f }
	, m_MaxVelocity{ 1000.0f }
	, m_Pos{ pos }
	, m_Acceleration{ Point2f() }
	, m_Velocity{ Point2f() }
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

bool Ball::GetSleepingState()
{
	return m_IsSleeping;
}

int Ball::GetId()
{
	return m_Id;
}

Point2f Ball::GetPosition()
{
	return m_Pos;
}

Point2f Ball::GetVelocity()
{
	return m_Velocity;
}

float Ball::GetSize()
{
	return m_Size;
}

void Ball::SetPosition(const Point2f& pos)
{
	m_Pos = pos;
}

void Ball::BounceHorizontal(const Point2f& colliderCenter, float collisionOverlap)
{
	const float loss{ 0.8f };

	if (m_Pos.x < colliderCenter.x)			m_Pos.x -= m_Size - collisionOverlap;
	else if (m_Pos.x > colliderCenter.x)	m_Pos.x += m_Size - collisionOverlap;

	m_Velocity.x *= -1;
	m_Velocity.x *= loss;
	m_Velocity.y *= loss;
}

void Ball::BounceVertical(const Point2f& colliderCenter, float collisionOverlap)
{
	const float loss{ 0.8f };

	if (m_Pos.y < colliderCenter.y)			m_Pos.y -= m_Size - collisionOverlap;
	else if (m_Pos.y > colliderCenter.y)	m_Pos.y += m_Size - collisionOverlap;
	
	m_Velocity.y *= -1;
	m_Velocity.x *= loss;
	m_Velocity.y *= loss;
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
	m_Velocity.x = utils::Clamp(m_Force * (m_Pos.x - mousePos.x), -m_MaxVelocity, m_MaxVelocity);
	m_Velocity.y = utils::Clamp(m_Force * (m_Pos.y - mousePos.y), -m_MaxVelocity, m_MaxVelocity);

	m_IsSleeping = false;
}

void Ball::Update(float deltaTime)
{
	if (m_IsSleeping) return;

	const float drag{ 1.2f };
	m_Acceleration.x = -m_Velocity.x * drag;
	m_Acceleration.y = -m_Velocity.y * drag;

	m_Velocity.x += m_Acceleration.x * deltaTime;
	m_Velocity.y += m_Acceleration.y * deltaTime;
	m_Pos.x += m_Velocity.x * deltaTime;
	m_Pos.y += m_Velocity.y * deltaTime;

	if (fabsf((m_Velocity.x * m_Velocity.x) + (m_Velocity.y * m_Velocity.y)) < 0.25f)
	{
		m_Velocity.x = 0.0f;
		m_Velocity.y = 0.0f;
		m_IsSleeping = true;
	}
}

void Ball::Draw()
{
	if (m_IsSleeping) utils::SetColor(1.0f, 0.0f, 0.0f);
	else utils::SetColor(1.0f, 1.0f, 1.0f);

	utils::FillEllipse(m_Pos, m_Size, m_Size);
}

void Ball::DrawNextFrame(float deltaTime)
{
	const Point2f nextPos (m_Pos.x + (m_Velocity.x * deltaTime), m_Pos.y + (m_Velocity.y * deltaTime));

	utils::SetColor(0.2f, 0.2f, 0.2f, 0.2f);
	utils::FillEllipse(nextPos.x, m_Pos.y, m_Size / 2.0f, m_Size / 2.0f);
	utils::FillEllipse(m_Pos.x, nextPos.y, m_Size / 2.0f, m_Size / 2.0f);
}

void Ball::DrawShotLine(const Point2f& mousePos)
{
	const float angle { atan2f(m_Pos.y - mousePos.y, m_Pos.x - mousePos.x) };
	float length{ utils::GetDistance(m_Pos, mousePos) };
	length = utils::Clamp(length, 0.0f, 75.0f);
	const Point2f endpoint{ cosf(angle) * length + m_Pos.x, sinf(angle) * length + m_Pos.y };

	utils::SetColor(0.2f, 0.2f, 0.4f);
	utils::DrawLine(m_Pos, endpoint, 4.0f);
}
