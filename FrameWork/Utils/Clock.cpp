
#include "Clock.h"

float GameEngine::Clock::GetFPS()
{
    return 1.0f / (__DELTA_TIME);
}

float GameEngine::Clock::GetDeltaTime()
{
    return __DELTA_TIME * __TIME_SCALE;
}

int GameEngine::Clock::Initialize()
{
    __DELTA_TIME = 0.0f;

    __START_TIME = std::chrono::steady_clock::now();
    __CURRENT_TIME = __START_TIME;
    __LAST_TIME = __START_TIME;

    __INITIALIZED = true;
	return 0;
}

void GameEngine::Clock::Tick(float deltaTime)
{
    __LAST_TIME = __CURRENT_TIME;
    __CURRENT_TIME = std::chrono::steady_clock::now();
    __ELAPSED = __CURRENT_TIME - __LAST_TIME;

    if (__INITIALIZED)
    {
        __DELTA_TIME = __ELAPSED.count() > 0.1 ? 0.1f : static_cast<float>(__ELAPSED.count());
    }
    else
        Initialize();
}