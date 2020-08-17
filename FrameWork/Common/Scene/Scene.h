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
  class GameObject;
  class Light;
  class Scene
  {
  private:
    /* data */
  public:
    Scene(/* args */);

    ~Scene();

    void initScene();

    void Update();

    void updateCamera(std::shared_ptr< GameObject> gb);

    std::string m_Name;

    //std::vector<std::shared_ptr< Camera>> m_Cameras;
    //std::vector< std::shared_ptr<Light >> m_Lights;
	  std::shared_ptr<GameObject> gameObject;
  };

} // namespace GameEngine

#endif