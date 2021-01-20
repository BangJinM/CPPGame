#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include <list>
#include <memory>

#include "Config.h"
#include "Object.h"
GameEngineBegin

class Camera;
class GameObject;
class Renderer;
class CanvasRenderer;
class Scene:public Object
{
private:
  /* data */
public:
  Scene(/* args */);

  ~Scene();

  void Update();

  void AddGameObject(SharedGameObject gameobject);
  void AddGameObject(SharedGameObject gameobject, SharedGameObject parent);
  SharedGameObject GetRootGameObject();

  std::string m_Name;

  void RenderAll();
  void AddCamera(SharePtr<Camera> camera);
  void RemoveCamera();

  void PrepareAll();
  void AddRenderer(SharePtr<Renderer> renderer);
  void RemoveRenderer();

  SharePtr<CanvasRenderer> GetCanvasRenderer();
  void SetCanvasRenderer(SharePtr<CanvasRenderer> canvas);

  SharedGameObject GetGObject(SharedGameObject parent, int sid);
  std::list<SharePtr<Renderer>> GetRenderer() { return m_Renderers; }

  std::list<SharePtr<Camera>> m_Cameras;
  std::list<SharePtr<Renderer>> m_Renderers;
  SharePtr<CanvasRenderer> m_Canvas;
  SharedGameObject m_Root;
};

GameEngineEnd
