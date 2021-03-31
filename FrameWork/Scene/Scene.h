#pragma once

#include <cstdint>
#include <list>
#include <memory>
#include <string>
#include <vector>
#include <map>

#include "Config.h"
#include "IBehaviour.h"
#include "Object.h"
#include "Cube.h"
namespace GameEngine
{
    class Camera;
    class GameObject;
    class Renderer;
    // class CanvasRenderer;
    class Light;
    class Scene : public Object, public IBehaviour
    {
    private:
        /* data */
    public:
        Scene(/* args */);

        ~Scene();

        virtual void Start() override;
        virtual void OnEnable() override;
        virtual void Update() override;
        virtual void Destory() override;

        void AddGameObject(SharedGameObject gameobject);
        void AddGameObject(SharedGameObject gameobject, SharedGameObject parent);

        std::string m_Name;

        void AddCamera(SharePtr<Camera> camera);
        void RemoveCamera(SharePtr<Camera> camera);
        std::vector<SharePtr<Camera>> GetCamera();

        void AddLight(SharePtr<Light> light);
        void RemoveLight(SharePtr<Light> light);
		std::vector<SharePtr<Light>> GetLights();

        SharedGameObject GetChildByName(std::string name);

        std::map<int, SharedGameObject> GetChildren();

        virtual void OnSerialize(cJSON* root) override;
        virtual void OnDeserialize(cJSON* root) override;

        SharedCube GetCube();

        std::vector<SharedGameObject> m_GameObjects;
        std::vector<SharePtr<Camera>> m_Cameras;
        std::vector<SharePtr<Light>> m_Lights;

        SharedGameObject m_Root;

    private:
        SharedCube cube;
    };

}  // namespace GameEngine
