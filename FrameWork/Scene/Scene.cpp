#include "Scene.h"

//һ�²���
#include "Camera.h"
#include "GameObject.h"
#include "Light.h"
#include "Mesh.h"
#include "MyMath.h"
#include "Renderer.h"
#include "Transform.h"

namespace GameEngine
{
    Scene::Scene()
    {
        m_Root = GameObject::CreateGameObject();
        m_Root->SetName("root");

        // auto canvas = GameObject::CreateGameObject();
        // canvas->SetName("Canvas");
        // m_Root->AddChild(canvas);
        // canvas->AddComponent<CanvasRenderer>(std::make_shared<CanvasRenderer>());
    }

    void Scene::AddGameObject(SharedGameObject gameobject)
    {
        m_Root->AddChild(gameobject);
    }

    void Scene::AddGameObject(SharedGameObject gameobject, SharedGameObject parent)
    {
    }

    Scene::~Scene()
    {
        m_Cameras.clear();
    }

    void Scene::Start()
    {
        auto children = m_Root->GetChildren();
        for (auto i = children.begin(); i != children.end(); i++)
        {
            i->second->Start();
        }
    }

    void Scene::OnEnable() {}

    void Scene::Update()
    {
        auto children = m_Root->GetChildren();
        for (auto i = children.begin(); i != children.end(); i++)
        {
            i->second->Update();
        }
    }

    void Scene::Destory()
    {
        auto children = m_Root->GetChildren();
        for (auto i = children.begin(); i != children.end(); i++)
        {
            i->second->Destory();
        }
    }

    void Scene::RemoveCamera(SharePtr<Camera> camera)
    {
        for (auto i = m_Cameras.begin(); i != m_Cameras.end(); i++)
        {
            if (*i == camera)
                m_Cameras.erase(i);
        }
    }

    void Scene::AddCamera(SharePtr<Camera> camera)
    {
        m_Cameras.push_back(camera);
    }

    std::vector<SharePtr<Camera>> Scene::GetCamera()
    {
        return m_Cameras;
    }

    void Scene::AddLight(SharePtr<Light> light)
    {
        m_Lights.push_back(light);
    }

    void Scene::RemoveLight(SharePtr<Light> light)
    {
        for (auto i = m_Lights.begin(); i != m_Lights.end(); i++)
        {
            if (*i == light)
                m_Lights.erase(i);
        }
    }

    std::vector<SharePtr<Light>> Scene::GetLights()
    {
        return m_Lights;
    }

    SharedGameObject Scene::GetChildByName(std::string name)
    {
        std::map<int, SharedGameObject> children = m_Root->GetChildren();
        SharedGameObject result;
        for (auto kv : children)
        {
            if (kv.second->GetName() == name)
            {
                return kv.second;
            }
            else
            {
                auto res = kv.second->GetChildByName(name);
                if (res)
                    return res;
            }
        }
        return SharedGameObject();
    }

    std::map<int, SharedGameObject> Scene::GetChildren()
    {
        return m_Root->GetChildren();
    }

    void Scene::OnSerialize(cJSON* root)
    {
        auto gameobjects = cJSON_AddArrayToObject(root, "Gameobjects");
        if (cube)
        {
            auto cjconCube = cJSON_AddObjectToObject(root, "Cube");
            cube->OnSerialize(cjconCube);
        }
        for (auto child : m_Root->GetChildren())
        {
            auto item = cJSON_CreateObject();
            child.second->OnSerialize(item);
            cJSON_AddItemToArray(gameobjects, item);
        }
    }

    void Scene::OnDeserialize(cJSON* root)
    {
        auto paramsNode = cJSON_GetObjectItem(root, "Cube");
        if (paramsNode)
        {
            cube = std::make_shared<Cube>();
            cube->OnDeserialize(paramsNode);
        }
        paramsNode = cJSON_GetObjectItem(root, "Gameobjects");
        for (auto index = 0; index < cJSON_GetArraySize(paramsNode); ++index)
        {
            auto childParam = cJSON_GetArrayItem(paramsNode, index);
            auto childNode = GameObject::CreateGameObject();
            childNode->OnDeserialize(childParam);
            AddGameObject(childNode);
        }
    }

    SharedCube Scene::GetCube()
    {
        return cube;
    }
}  // namespace GameEngine
