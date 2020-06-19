#ifndef GameEngine_Interface_ISceneParser_H
#define GameEngine_Interface_ISceneParser_H
#include <memory>
#include <string>
#include "GameObject.h"
#include "ObjLoader.h"
namespace GameEngine
{
	class Scene;
    class ISceneParser
    {
    public:
        virtual std::unique_ptr<GameObject> Parse(std::vector<tinyobj::shape_t>) = 0;
    };
} // namespace GameEngine
#endif