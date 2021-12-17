#include "pch.h"
#include "Game.h"
#include "Ball.h"
#include "Level.h"
#include <iostream>
#include <sstream>
#include <iomanip>

#pragma region gameFunctions
void Start()
{
	g_Levels.emplace_back
	(
		Level
		(Point2f(g_WindowWidth / 2.0f, g_WindowHeight / 5.0f)
		, Point2f(g_WindowWidth / 2.0f, (g_WindowHeight / 5.0f) * 4.0f)
		, Texture()
		, 25.0f)
	);

	g_pCurrentLevel = &g_Levels[0];

	SpawnBall();
	GenerateLevel();
}

void Draw()
{
	ClearBackground(0.2f, 0.75f, 0.2f);
	if (g_pCurrentLevel)
	{
		g_pCurrentLevel->Draw();
	}
	
	if (g_pBall)
	{
		g_pBall->Draw();
		
		if (g_pBall->IsSelected())
		{
			g_pBall->DrawShotLine(g_MousePos);
		}
	}

	DrawFramerateUI();
}

void Update(float elapsedSec)
{
	g_DeltaTime = elapsedSec;
	g_SimDeltaTime = g_DeltaTime / float(g_NrSimulationUpdates);
	g_NrFrames++;

	if (g_pBall)
	{	
		for (int i = 0; i < g_NrSimulationUpdates; i++)
		{
			CollisionUpdate();
			g_pBall->Update(g_SimDeltaTime);
		}

		
		if (g_pCurrentLevel->IsInHole(g_pBall->GetPosition(), g_pBall->GetSize()))
		{
			delete g_pBall;
			g_pBall = nullptr;
		}
	}

	UpdateFramerate();
}

void End()
{

}
#pragma endregion gameFunctions

#pragma region inputHandling											
void OnKeyDownEvent(SDL_Keycode key)
{

}

void OnKeyUpEvent(SDL_Keycode key)
{
	
}

void OnMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	g_MousePos = Point2f(float(e.x), float(g_WindowHeight - e.y));
}

void OnMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	if (e.button == SDL_BUTTON_LEFT)
	{
		if (g_pBall->IsPointInCircle(g_MousePos))
		{
			g_pBall->Select();
		}
	}
}

void OnMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	if (e.button == SDL_BUTTON_LEFT)
	{
		if (!g_pBall) return;

		if (g_pBall->IsSelected())
		{
			g_pBall->Shoot(g_MousePos);
		}

		g_pBall->Deselect();
	}
}
#pragma endregion inputHandling

#pragma region ownDefinitions
void SpawnBall()
{
	delete g_pBall;
	g_pBall = new Ball(0, g_pCurrentLevel->GetStartPos(), 16.0f);
}

void GenerateLevel()
{
	enum class TileType
	{
		Air,
		Wall,
		Hole,
		Ball
	};

	const int tileSize{ 64 };
	const int map[13][9]
	{
		{1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 2, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 1, 1, 1, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 3, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1}
	};

	std::vector<Tile> tileMap{};

	for (int y = 12; y >= 0; y--)
	{
		for (int x = 0; x < 9; x++)
		{
			Point2f tilePos{ (64.0f * x) - 64.0f, (64.0f * (12 - y)) - 64.0f };
			const Tile tile{ tilePos, Texture(), float(tileSize) };

			switch (map[y][x])
			{
			case int(TileType::Wall):
				tileMap.emplace_back(tile);
				break;
			case int(TileType::Hole):
				tilePos.x += tileSize / 2.0f;
				tilePos.y += tileSize / 2.0f;
				g_pCurrentLevel->SetHolePos(tilePos);
				break;
				case int(TileType::Ball) :
					tilePos.x += tileSize / 2.0f;
					tilePos.y += tileSize / 2.0f;
					g_pBall->SetPosition(tilePos);
					break;
			}
		}
	}

	g_pCurrentLevel->SetTiles(tileMap);
}

void CollisionUpdate()
{
	if (g_pBall->GetSleepingState()) return;

	const Point2f pos{ g_pBall->GetPosition() };
	const Point2f vel{ g_pBall->GetVelocity() };
	const float size{ g_pBall->GetSize() };
	const Point2f newPos{ pos.x + (vel.x * g_SimDeltaTime), pos.y + (vel.y * g_SimDeltaTime) };

	for (auto& tile : g_pCurrentLevel->GetTiles())
	{
		Point2f nearestPoint = GetBBNearest(Point2f(newPos.x, pos.y), size, tile);
		float distance = utils::GetDistance(Point2f(newPos.x, pos.y), nearestPoint);

		if (distance < size)
		{
			g_pBall->BounceHorizontal(Point2f(tile.pos.x + tile.size / 2.0f, tile.pos.y + tile.size / 2.0f), distance);
		}
		
		nearestPoint = GetBBNearest(Point2f(pos.x, newPos.y), size, tile);
		distance = utils::GetDistance(Point2f(pos.x, newPos.y), nearestPoint);
		if (distance < size)
		{
			g_pBall->BounceVertical(Point2f(tile.pos.x + tile.size / 2.0f, tile.pos.y + tile.size / 2.0f), distance);
		}
	}
}
bool CheckCollision(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2)
{
	return x1 + w1 > x2 && x1 < x2 + w2 && y1 + h1 > y2 && y1 < y2 + h2;
}

Point2f GetBBNearest(const Point2f& circleCenter, float circleRadius, const Tile& tile)
{
	const Point2f tileCenter{ tile.pos.x + (tile.size / 2.0f), tile.pos.y + (tile.size / 2.0f) };
	Point2f difference{ circleCenter.x - tileCenter.x, circleCenter.y - tileCenter.y};

	difference.x = utils::Clamp(difference.x, -tile.size / 2.0f, tile.size / 2.0f);
	difference.y = utils::Clamp(difference.y, -tile.size / 2.0f, tile.size / 2.0f);

	const Point2f closest{ tileCenter.x + difference.x, tileCenter.y + difference.y };

	return closest;
}

void UpdateFramerate()
{
	g_AvgFrameTime += g_DeltaTime;
	if (g_NrFrames % 100 == 0)
	{
		g_AvgFrameRate = 1.0f / (g_AvgFrameTime / 100.0f);
		g_AvgFrameTime = 0.0f;
	}

	RefreshFramerateUI();
}

void RefreshFramerateUI()
{
	DeleteTexture(g_FPSCounter);

	std::stringstream stream;
	stream << std::fixed << std::setprecision(0) << g_AvgFrameRate;
	std::string s = stream.str();
	TextureFromString(s, "resources/font.ttf", 24, Color4f(1.0f, 1.0f, 1.0f, 1.0f), g_FPSCounter);
}

void DrawFramerateUI()
{
	const Point2f pos{ 10.0f, 10.0f };
	DrawTexture(g_FPSCounter, pos);
}
#pragma endregion ownDefinitions