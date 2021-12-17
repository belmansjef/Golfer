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

void Level::SetTiles(const std::vector<Tile>& tiles)
{
	m_Tiles = tiles;
}

void Level::SetHolePos(const Point2f& pos)
{
	m_HolePos = pos;
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
	for (auto& tile : m_Tiles)
	{
		utils::SetColor(0.0f, 0.0f, 0.2f, 0.3f);
		utils::FillRect(tile.pos.x, tile.pos.y + 10.0f, tile.size, tile.size);

		utils::SetColor(0.5f, 0.5f, 0.5f);
		utils::FillRect(tile.pos, tile.size, tile.size);

		utils::SetColor(0.0f, 0.0f, 0.0f);
		utils::DrawRect(tile.pos, tile.size, tile.size, 2.0f);
	}


    // Draw hole
	utils::SetColor(0.0f, 0.0f, 0.0f, 0.2f);
	utils::FillEllipse(m_HolePos.x, m_HolePos.y + (m_HoleSize / 3.0f), m_HoleSize, m_HoleSize);

	utils::SetColor(0.0f, 0.0f, 0.0f);
	utils::FillEllipse(m_HolePos, m_HoleSize, m_HoleSize);
}
