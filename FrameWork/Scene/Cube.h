#pragma once

#include <list>
#include <vector>

#include "Component.h"
#include "Config.h"
#include "MyMath.h"

namespace GameEngine
{
    class Cube : public Component
    {
    public:
        Cube(ClassIDType classID = ClassID(Cube));

        virtual void OnSerialize(cJSON* root) override;
        virtual void OnDeserialize(cJSON* root) override;
        CubeValue GetValueByDir(int dir);

        void SetTextureID(int id);
        int GetTextureID();

        SharedMesh GetMesh();

    protected:
        SharedMesh m_Mesh;
        std::string m_MeshPath;
        CubeValue values[6];
        int textureID = -1;
    };
}  // namespace GameEngine
