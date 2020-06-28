#ifndef GameEngine_Common_Scene_H
#define GameEngine_Common_Scene_H

#include <cstdint>
#include <vector>
#include <string>

#include "Scene.h"

namespace GameEngine
{
  class Camera;
  class GameObject;
  class BaseObject;
  class Scene
  {
  private:
    /* data */
  public:
    Scene(/* args */);
    ~Scene();
    void addChild(BaseObject *child);
    void deleteChild(BaseObject *child);
    void Draw();
    void initScene();
    void updateCamera();
    std::string m_Name;
    std::vector<Camera *> m_Cameras;
    std::vector<GameObject *> m_Gameobjects;
  };

} // namespace GameEngine

#endif