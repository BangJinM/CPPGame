#ifndef GameEngine_ObjParser_H
#define GameEngine_ObjParser_H

#include "ISceneParser.h"
#include <vector>
namespace GameEngine
{
	class Scene;
	class ObjParser : public ISceneParser
	{

	public:
		virtual std::unique_ptr<Scene> Parse(const std::string &buf){
			return std::unique_ptr<Scene>();
		}

	}; // namespace GameEngine

} // namespace GameEngine

#endif