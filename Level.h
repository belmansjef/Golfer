#pragma once
#include "pch.h"

#pragma region Tile Struct
struct Tile
{
	Tile();
	explicit Tile(const Point2f& pos, const utils::Texture& texture, float size);

	Point2f pos;
	utils::Texture texture;
	float size;
};
#pragma endregion

class Level
{
private:
	Point2f m_StartPos{};
	Point2f m_HolePos{};
	std::vector<Tile> m_Tiles{};
	utils::Texture m_BackgroundTexture{};
	float m_HoleSize{};

public:
	Level();
	Level(const Point2f& startPos, const Point2f& holePos, const utils::Texture& backgroundTexture, float holeSize);

	bool IsInHole(const Point2f& pos, float size);
	std::vector<Tile> GetTiles();
	Point2f GetStartPos();
	Point2f GetHolePos();

	void Draw();
};