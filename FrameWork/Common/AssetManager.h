#pragma once

#include <list>
#include <map>
#include <functional>
#include <memory>

#include "Mesh.h"
#include "Config.h"
#include "UI/Font.h"
#include "Texture.h"
#include "Material.h"
#include "GameObject.h"
#include "IRuntimeModule.h"

#include <ft2build.h>
#include FT_FREETYPE_H

GameEngineBegin 

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

GameEngineEnd
