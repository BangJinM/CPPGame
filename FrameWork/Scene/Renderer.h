#pragma once

#include <list>
#include <string>
#include <vector>

#include "Component.h"
#include "Config.h"
#include "MyMath.h"

namespace GameEngine::ger
{
    class InputAssembler;
    class GERBuffer;
    class Shader;
}

namespace GameEngine
{
    class Camera;
    class Mesh;
    class Renderer : public Component
    {
    public:
        Renderer();
        ~Renderer();
        void Prepare();

        SharedMesh GetMesh();
        std::vector<std::string> GetMaterialPaths();

        virtual void OnSerialize(cJSON *root) override;
        virtual void OnDeserialize(cJSON *root) override;


        std::vector<ger::InputAssembler *> inputs;
        std::vector<ger::Shader *> shaders;
    protected:
        std::vector<std::string> m_MaterialPaths;
        std::vector<ger::InputAssembler *> inputAssemblers;
        std::string m_MeshPath;
        SharedMesh m_Mesh;
    };
} // namespace GameEngine
