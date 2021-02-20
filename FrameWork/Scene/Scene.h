#pragma once

#include <cstdint>
#include <list>
#include <memory>
#include <string>
#include <vector>

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
        SharedGameObject GetRootGameObject();

        std::string m_Name;

        void AddCamera(SharePtr<Camera> camera);
        void RemoveCamera(SharePtr<Camera> camera);

        void AddLight(SharePtr<Light> light);
        void RemoveLight(SharePtr<Light> light);
		std::list<SharePtr<Light>> GetLights();

        void AddRenderer(SharePtr<Renderer> renderer);
        void RemoveRenderer();

        // SharePtr<CanvasRenderer> GetCanvasRenderer();
        // void SetCanvasRenderer(SharePtr<CanvasRenderer> canvas);

        SharedGameObject GetGObject(SharedGameObject parent, int sid);
        std::list<SharePtr<Renderer>> GetRenderer() { return m_Renderers; }

        virtual void OnSerialize(cJSON* root) override;
        virtual void OnDeserialize(cJSON* root) override;

        SharedCube GetCube();

        std::list<SharePtr<Camera>> m_Cameras;
        std::list<SharePtr<Light>> m_Lights;
        std::list<SharePtr<Renderer>> m_Renderers;
        // SharePtr<CanvasRenderer> m_Canvas;
        SharedGameObject m_Root;

    private:
        SharedCube cube;
    };

}  // namespace GameEngine
