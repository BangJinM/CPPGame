#pragma once

#include "IRuntimeModule.h"
#include <list>
#include <map>
#include <functional>
#include <memory>

#include "Texture.h"
#include "GameObject.h"
#include "Material.h"
#include "Mesh.h"
#include "UI/Font.h"

#include <ft2build.h>
#include FT_FREETYPE_H

namespace GameEngine
{
    class AssetManager : IRuntimeModule
    {
    private:


    public:
        virtual int Initialize();
        virtual void Finalize();
        virtual void Tick();

        static std::shared_ptr<GameObject> LoadGameObject(const std::string &path);
        static std::shared_ptr<Mesh> LoadMesh(const std::string &path);
        static std::shared_ptr<Texture> LoadTexture(const std::string &path);
        static std::shared_ptr<Material> LoadMaterial(const std::string &path);

        // static std::shared_ptr<Font> GetFont(const std::string &path);
        static std::shared_ptr<Texture> GetTexture(const std::string &path);
        static void AddTexture(const std::string &path, std::shared_ptr<Texture> image);

        static std::shared_ptr<Texture> getWhiteTexture();
    };

} // namespace GameEngine
