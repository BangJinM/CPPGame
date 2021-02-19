#include "Cube.h"

#include "AssetManager.h"
namespace GameEngine
{
    extern AssetManager* g_pAssetManager;

    Cube::Cube()
    {
        m_ClassID = ClassID(Cube);
    }

    void Cube::OnSerialize(cJSON* root)
    {
        Component::OnSerialize(root);
        auto cjsonValues = cJSON_AddArrayToObject(root, "CubeVaules");
        SerializableHelper::Seserialize(root, "m_Mesh", m_MeshPath);
        for (size_t i = 0; i < 6; i++)
        {
            auto item = cJSON_CreateObject();
            SerializableHelper::Seserialize(item, "dir", values[i].dir);
            SerializableHelper::Seserialize(item, "path", values[i].path);
            cJSON_AddItemToArray(cjsonValues, item);
        }
    }
    void Cube::OnDeserialize(cJSON* root)
    {
        Component::OnDeserialize(root);
        auto paramsNode = cJSON_GetObjectItem(root, "CubeVaules");
        m_MeshPath = SerializableHelper::DeserializeString(root, "m_Mesh");
        m_Mesh = g_pAssetManager->LoadMesh(m_MeshPath);
        for (auto index = 0; index < cJSON_GetArraySize(paramsNode); ++index)
        {
            auto compParam = cJSON_GetArrayItem(paramsNode, index);
            CubeValue value;
            value.dir = static_cast<CubeDir>(SerializableHelper::DeserializeInt(compParam, "dir"));
            value.path = SerializableHelper::DeserializeString(compParam, "path");
            if (value.dir >= 0 && value.dir <= 6)
                values[value.dir - 1] = value;
        }
    }

    CubeValue Cube::GetValueByDir(int dir)
    {
        return values[dir];
    }

    void Cube::SetTextureID(int id)
    {
        textureID = id;
    }

    int Cube::GetTextureID()
    {
        return textureID;
    }
    SharedMesh Cube::GetMesh()
    {
        return m_Mesh;
    }
}  // namespace GameEngine