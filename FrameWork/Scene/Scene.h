#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include <list>
#include <memory>

#include "Config.h"
#include "Object.h"
#include "IComponent.h"
GameEngineBegin

    class Camera;
class GameObject;
class Renderer;
class CanvasRenderer;
class Light;
class Scene : public Object, public IComponent
{
private:
  /* data */
public:
  Scene(/* args */);

  ~Scene();

  virtual void Start() override;
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

  void AddRenderer(SharePtr<Renderer> renderer);
  void RemoveRenderer();

  SharePtr<CanvasRenderer> GetCanvasRenderer();
  void SetCanvasRenderer(SharePtr<CanvasRenderer> canvas);

  SharedGameObject GetGObject(SharedGameObject parent, int sid);
  std::list<SharePtr<Renderer>> GetRenderer() { return m_Renderers; }

  std::list<SharePtr<Camera>> m_Cameras;
  std::list<SharePtr<Light>> m_Lights;
  std::list<SharePtr<Renderer>> m_Renderers;
  SharePtr<CanvasRenderer> m_Canvas;
  SharedGameObject m_Root;
};

GameEngineEnd
