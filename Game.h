#pragma once
using namespace utils;
using namespace std;
#pragma region gameInformation
std::string g_WindowTitle{ "Golfer - Belmans, Jef - 1DAE21" };

float g_WindowWidth{ 448 };
float g_WindowHeight{ 704 };
#pragma endregion gameInformation

#pragma region ownDeclarations
class Ball;
class Level;

float g_DeltaTime{};

Ball* g_pBall{};

vector<Level> g_Levels{};
Level* g_pCurrentLevel{};

void SpawnBall();
#pragma endregion ownDeclarations

#pragma region gameFunctions											
void Start();
void Draw();
void Update(float elapsedSec);
void End();
#pragma endregion gameFunctions

#pragma region inputHandling											
void OnKeyDownEvent(SDL_Keycode key);
void OnKeyUpEvent(SDL_Keycode key);
void OnMouseMotionEvent(const SDL_MouseMotionEvent& e);
void OnMouseDownEvent(const SDL_MouseButtonEvent& e);
void OnMouseUpEvent(const SDL_MouseButtonEvent& e);
#pragma endregion inputHandling
