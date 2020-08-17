#include "Renderer.h"

namespace GameEngine
{
    void Renderer::Prepare()
    {
        for (int i = 0; i < m_Materials.size(); ++i)
        {
            auto &material = m_Materials[i];
            if (material)
            {
                material->Prepare();
            }
        }
    }

    Renderer::Renderer() : Component(ClassIDType::CLASS_Undefined)
    {
    }
} // namespace GameEngine
