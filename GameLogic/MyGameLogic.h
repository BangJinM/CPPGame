#pragma once
#include "GameLogic.h"
namespace GameEngine
{
    class MyGameLogic : public GameLogic
    {
    private:
    public:
        virtual int Initialize() override;
        virtual void Finalize() override;
        virtual void Tick() override;
    };
}  // namespace GameEngine
