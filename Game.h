#pragma once
using namespace utils;
using namespace std;
#pragma region gameInformation
std::string g_WindowTitle{ "Golfer - Belmans, Jef - 1DAE21" };

float g_WindowWidth{ 448 };
float g_WindowHeight{ 704 };
#pragma endregion gameInformation

#pragma region ownDeclarations
struct Tile;
class Ball;
class Level;

float g_DeltaTime{};
float g_AvgFrameTime{};
float g_AvgFrameRate{};
int g_NrFrames{};
Texture g_FPSCounter{};

int g_NrSimulationUpdates{ 100 };
float g_SimDeltaTime{};

Point2f g_MousePos{};

Ball* g_pBall{};

vector<Level> g_Levels{};
Level* g_pCurrentLevel{};

void SpawnBall();
void GenerateLevel();

void CollisionUpdate();
bool CheckCollision(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2);
Point2f GetBBNearest(const Point2f& circleCenter, float circleRadius, const Tile& tile);

void UpdateFramerate();
void RefreshFramerateUI();
void DrawFramerateUI();
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
