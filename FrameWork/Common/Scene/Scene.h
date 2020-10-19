#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include <list>
#include <memory>

#include "Config.h"

GameEngineBegin 

class Camera;
class GameObject;
class Renderer;
class CanvasRenderer;
class Scene
{
private:
  /* data */
public:
  Scene(/* args */);

  ~Scene();

  void LoadSceneByPath(std::string path);

  void Update();

  void AddGameObject(std::shared_ptr<GameObject> gameobject);
  void AddGameObject(std::shared_ptr<GameObject> gameobject, std::shared_ptr<GameObject> parent);
  std::shared_ptr<GameObject> GetRootGameObject();

  std::string m_Name;

  void RenderAll();
  void AddCamera(std::shared_ptr<Camera> camera);
  void RemoveCamera();

  void PrepareAll();
  void AddRenderer(std::shared_ptr<Renderer> renderer);
  void RemoveRenderer();

  std::shared_ptr<CanvasRenderer> GetCanvasRenderer();
  void SetCanvasRenderer(std::shared_ptr<CanvasRenderer> canvas);

  std::shared_ptr<GameObject> GetObject(std::shared_ptr<GameObject> parent, int sid);
  std::list<std::shared_ptr<Renderer>> GetRenderer() { return m_Renderers; }

  std::list<std::shared_ptr<Camera>> m_Cameras;
  std::list<std::shared_ptr<Renderer>> m_Renderers;
  std::shared_ptr<CanvasRenderer> m_Canvas;
  std::shared_ptr<GameObject> m_Root;
};

GameEngineEnd
