#pragma once
#include "GameLogic.h"

namespace GameEngine
{
	class Scene;
    class MyGameLogic : public GameLogic
    {
    private:
		SharePtr<Scene> m_Scene;
    public:
        virtual int Initialize() override;
        virtual void Finalize() override;
        virtual void Tick(float deltaTime) override;

    };
}  // namespace GameEngine
