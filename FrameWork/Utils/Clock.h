#pragma once

#include <chrono>
#include <string>

#include "IRuntimeModule.h"

namespace GameEngine
{
    class Clock : public IRuntimeModule
    {
    public:
        float GetFPS();

        virtual int Initialize() override;
        virtual void Tick(float deltaTime) override;
        virtual void Finalize() override {}

        float GetDeltaTime();

    private:
        std::chrono::steady_clock::time_point __START_TIME;
        std::chrono::steady_clock::time_point __LAST_TIME;
        std::chrono::steady_clock::time_point __CURRENT_TIME;
        std::chrono::duration<double> __ELAPSED;

        bool __INITIALIZED = false;
        float __TIME_SCALE = 1.0f;
        float __DELTA_TIME = 0.0f;
        float __TIME_SINCE_START = 0.0f;
    };

}  // namespace GameEngine