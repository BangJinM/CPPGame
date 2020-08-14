#ifndef GameEngine_Common_AssetManager_H
#define GameEngine_Common_AssetManager_H

#include "IRuntimeModule.h"
#include <list>
#include <map>
#include <functional>
#include <memory>

#include "Image.h"
#include "GameObject.h"
#include "Material.h"
#include "Mesh.h"

namespace GameEngine
{
    class AssetManager : IRuntimeModule
    {
    public:
        virtual int Initialize();
        virtual void Finalize();
        virtual void Tick();

        static std::shared_ptr<GameObject> LoadGameObject(const std::string &path);
        static std::shared_ptr<Mesh> LoadMesh(const std::string &path);
        static std::shared_ptr<Image> LoadTexture(const std::string &path);
        static std::shared_ptr<Material> LoadMaterial(const std::string &path);
    };

} // namespace GameEngine
#endif