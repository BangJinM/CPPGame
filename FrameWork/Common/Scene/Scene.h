#ifndef GameEngine_Common_Scene_H
#define GameEngine_Common_Scene_H

#include <cstdint>
#include "ISceneParser.h"
#include "Scene.h"
namespace GameEngine
{
  class Scene
  {
  private:
    /* data */
  public:
    Scene(/* args */);
    ~Scene();

    GameObject* getFirstGameObject();
    void Draw();

    GameObject *gameobject;
    GameObject *cameraObject;
  };

} // namespace GameEngine

#endif