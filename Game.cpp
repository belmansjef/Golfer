#include "pch.h"
#include "Game.h"
#include "Ball.h"
#include "Level.h"
#include <iostream>

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
	}
}

void Update(float elapsedSec)
{
	g_DeltaTime = elapsedSec;
	if (g_pBall)
	{
		g_pBall->Update(g_DeltaTime, g_WindowWidth, g_WindowHeight);

		if (g_pCurrentLevel->IsInHole(g_pBall->GetPosition(), g_pBall->GetSize()))
		{
			delete g_pBall;
			g_pBall = nullptr;
		}
	}
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
	
}

void OnMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	const Point2f mousePos{ Point2f(float(e.x), float(g_WindowHeight - e.y)) };

	if (e.button == SDL_BUTTON_LEFT)
	{
		if (g_pBall->IsPointInCircle(mousePos))
		{
			g_pBall->Select();
		}
	}
	
}

void OnMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	const Point2f mousePos{ Point2f(float(e.x), float(g_WindowHeight - e.y)) };

	if (e.button == SDL_BUTTON_LEFT)
	{
		if (g_pBall->IsSelected())
		{
			g_pBall->Shoot(mousePos);
		}

		g_pBall->Deselect();
	}
}
#pragma endregion inputHandling

#pragma region ownDefinitions
void SpawnBall()
{
	delete g_pBall;
	g_pBall = new Ball(0, g_pCurrentLevel->GetStartPos(), 20.0f);
}
#pragma endregion ownDefinitions