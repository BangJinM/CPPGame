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

    static SharedGameObject LoadGameObject(const std::string &path);
    static SharedMesh LoadMesh(const std::string &path);
    static SharedTexture LoadTexture(const std::string &path);
    static SharedMaterial LoadMaterial(const std::string &path);

    // static SharePtr<Font> GetFont(const std::string &path);
    static SharedTexture GetTexture(const std::string &path);
    static void AddTexture(const std::string &path, SharedTexture image);

    static SharedTexture getWhiteTexture();
};

GameEngineEnd
