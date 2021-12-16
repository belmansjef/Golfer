#include "Level.h"

#pragma region Tile Constructor
Tile::Tile()
	: pos{ Point2f() }
	, texture{ utils::Texture() }
	, size{ 0.0f }
{
}

Tile::Tile(const Point2f& pos, const utils::Texture& texture, float size)
	: pos{ pos }
	, texture{ texture }
	, size{ size }
{
}

#pragma endregion

Level::Level()
	: m_StartPos{Point2f()}
	, m_HolePos{Point2f()}
	, m_Tiles{std::vector<Tile>()}
	, m_BackgroundTexture{utils::Texture()}
	, m_HoleSize{0.0f}
{
}

Level::Level(const Point2f& startPos, const Point2f& holePos, const utils::Texture& backgroundTexture, float holeSize)
	: m_StartPos{startPos}
	, m_HolePos{holePos}
	, m_Tiles{std::vector<Tile>()}
	, m_BackgroundTexture{backgroundTexture}
	, m_HoleSize{holeSize}
{
}

bool Level::IsInHole(const Point2f& pos, float size)
{
	const float distance{ utils::GetDistance(m_HolePos, pos) };

	return distance < m_HoleSize - size / 2.0f;
}

std::vector<Tile> Level::GetTiles()
{    
	return m_Tiles;
}

Point2f Level::GetStartPos()
{
	return m_StartPos;
}

Point2f Level::GetHolePos()
{
	return m_HolePos;
}

void Level::Draw()
{
    // Draw hole
	utils::SetColor(0.0f, 0.0f, 0.0f, 0.2f);
	utils::FillEllipse(m_HolePos.x, m_HolePos.y + (m_HoleSize / 3.0f), m_HoleSize, m_HoleSize);

	utils::SetColor(0.0f, 0.0f, 0.0f);
	utils::FillEllipse(m_HolePos, m_HoleSize, m_HoleSize);
}
