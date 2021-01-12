#pragma once
#include <cstdint>
#include <memory>

#include "Config.h"
#include "stb_image.h"
#include "Texture.h"
#include "AssetLoader.h"
#include "IParser.h"

GameEngineBegin extern GameEngineFile::AssetLoader *g_pAssetLoader;
GameEngineEnd
    UseGameEngine
        GameEngineParserBegin

    class TextureParser : public IParser
{
public:
    virtual SharedObject Parser(const std::string path) override
    {
        unsigned char *data;
        Buffer buffer = g_pAssetLoader->SyncOpenAndReadBinary(path.c_str());
        unsigned char *picData = reinterpret_cast<unsigned char *>(buffer.m_pData);

        int width, height, nrComponents;
        data = stbi_load_from_memory(picData, buffer.m_szSize, &width, &height, &nrComponents, 0);
        if (data)
        {
            SharedTexture image = std::make_shared<Texture>();
            image->Height = height;
            image->Width = width;
            image->data = data;
            image->formate = nrComponents;
            return image;
        }
        return SharedTexture();
    }
};

GameEngineParserEnd