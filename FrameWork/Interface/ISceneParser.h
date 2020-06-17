#ifndef GameEngine_Interface_ISceneParser_H
#define GameEngine_Interface_ISceneParser_H
#include <memory>
#include <string>
#include "GameObject.h"
namespace GameEngine
{
	class Scene;
    class ISceneParser
    {
    public:
        virtual std::unique_ptr<GameObject> Parse(const std::string &buf) = 0;
    };
} // namespace GameEngine
#endif