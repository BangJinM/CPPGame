#ifndef GameEngine_Common_Scene_Mesh_H
#define GameEngine_Common_Scene_Mesh_H

#include "ClassIDs.h"
#include "Component.h"
#include <vector>
namespace GameEngine
{
    class Mesh : public Component
    {
    public:
        Mesh();
    private:
        std::vector<float> m_Positions;
        std::vector<float> m_Normals;
        std::vector<float> m_Texcoords;
        std::vector<unsigned short> m_Indices;
        std::vector<int> m_MaterialIDs; // per-mesh material ID
    };
} // namespace GameEngine
#endif