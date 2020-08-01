#ifndef GameEngine_Common_Scene_H
#define GameEngine_Common_Scene_H

#include <cstdint>
#include <vector>
#include <string>

#include "Scene.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#define _DEBUG
#ifdef _DEBUG
#define new new (_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define DBG_NEW new
#endif

namespace GameEngine
{
  class Camera;
  class GameObject;
  class BaseObject;
  class Light;
  class Scene
  {
  private:
    /* data */
  public:
    Scene(/* args */);

    ~Scene();

    void Draw();

    void initScene();

    void updateCamera(BaseObject *gb);

    std::string m_Name;

    std::vector<Camera *> m_Cameras;
    std::vector<Light *> m_Lights;
    GameObject *gameObject;
  };

} // namespace GameEngine

#endif